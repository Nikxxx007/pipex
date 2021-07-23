#include "commands.h"
#include "signals.h"

static int		exec_processes_prepare(t_commlist *commands, t_envp *envp);
static int		exec_single_builtin(t_commlist *commands, t_envp *envp);
static void		exec_single_builtin__restore_fds(t_commlist *commands,
					int stdin_fd, int stdout_fd);
static size_t	count_procesess(t_commlist *commands);

int	command_processing(t_commlist **commands, t_envp *envp)
{
	int		status;
	int		exit_status;

	if (err_assign(commands__pipe_parser(*commands), &status) != EX_OK)
		return (status);
	if (err_assign(redir_left_double(commands, &exit_status), &status) != EX_OK)
		return (status);
	if (exit_status != EX_OK)
		return (exit_status);
	if (err_assign(redir_left_uno(commands), &status) != EX_OK)
		return (status);
	if (err_assign(redir_right_all(commands), &status) != EX_OK)
		return (status);
	return (exec_processes_prepare(*commands, envp));
}

static int	exec_processes_prepare(t_commlist *commands, t_envp *envp)
{
	int		*pids;
	size_t	size;
	size_t	index;
	int		status;

	size = count_procesess(commands);
	if (size == 0)
		return (0);
	if (size == 1 && is_builtin_command(commands->argv))
		return (exec_single_builtin(commands, envp));
	pids = malloc(sizeof(int) * size);
	if (!pids)
		return (perror__errno("sys", EX_OSERR));
	status = exec_all_processes(commands, envp, pids);
	if (status != EX_OK)
	{
		free(pids);
		return (status);
	}
	index = 0;
	while (index++ < size)
		if (waitpid(pids[index - 1], &status, 0) < 0)
			return (perror__errno("sys", EX_OSERR));
	free(pids);
	return (WEXITSTATUS(status));
}

static int	exec_single_builtin(t_commlist *commands, t_envp *envp)
{
	int	stdout_fd;
	int	stdin_fd;
	int	st;

	st = EX_OK;
	stdin_fd = STDIN_FILENO;
	if (commands->fd_in)
	{
		stdin_fd = dup(STDIN_FILENO);
		err_assign2(dup2(commands->fd_in, STDIN_FILENO), EX_OSERR, &st);
	}
	stdout_fd = STDOUT_FILENO;
	if (commands->fd_out)
	{
		stdout_fd = dup(STDOUT_FILENO);
		err_assign2(dup2(commands->fd_out, STDOUT_FILENO), EX_OSERR, &st);
	}
	if (st == EX_OK)
		st = handle_command(commands->argv, envp);
	exec_single_builtin__restore_fds(commands, stdin_fd, stdout_fd);
	return (st);
}

static void	exec_single_builtin__restore_fds(t_commlist *commands,
				int stdin_fd, int stdout_fd)
{
	if (commands->fd_in)
	{
		close(commands->fd_in);
		dup2(stdin_fd, STDIN_FILENO);
	}
	if (commands->fd_out)
	{
		close(commands->fd_out);
		dup2(stdout_fd, STDOUT_FILENO);
	}
}

static size_t	count_procesess(t_commlist *commands)
{
	size_t	count;

	count = 0;
	while (commands)
	{
		count++;
		commands = commands->next;
	}
	return (count);
}
