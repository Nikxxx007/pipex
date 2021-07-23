#include "commands.h"

static void	child_process_handler(t_commlist *commands, t_envp *envp);
static int	close_fds_n_switch(t_commlist **commands,
				t_commlist *command_copy, int all_flag);

int	exec_all_processes(t_commlist *commands, t_envp *envp, int *pids)
{
	ssize_t	index;
	int		st;

	st = EX_OK;
	index = -1;
	while (commands)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pids[++index] = fork();
		if (pids[index] < 0)
			return (perror__errno("sys", EX_OSERR));
		else if (pids[index] == 0)
			child_process_handler(commands, envp);
		close_fds_n_switch(&commands, NULL, 0);
	}
	return (st);
}

static void	child_process_handler(t_commlist *commands, t_envp *envp)
{
	int		st;

	st = EX_OK;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	err_assign2(dup2(commands->fd_in, STDIN_FILENO), EX_OSERR, &st);
	err_assign2(dup2(commands->fd_out, STDOUT_FILENO), EX_OSERR, &st);
	err_assign2(close_fds_n_switch(NULL, commands, 1), EX_OSFILE, &st);
	if (st == EX_OK)
		st = handle_command(commands->argv, envp);
	commlist_clear(commands);
	exit(st);
}

static int	close_fds_n_switch(t_commlist **commands,
				t_commlist *commands_copy, int all_flag)
{
	int	status;

	status = EX_OK;
	if (all_flag)
	{
		while (commands_copy)
		{
			if (commands_copy->fd_in != STDIN_FILENO)
				err_assign2(close(commands_copy->fd_in), EX_OSFILE, &status);
			if (commands_copy->fd_out != STDOUT_FILENO)
				err_assign2(close(commands_copy->fd_out), EX_OSFILE, &status);
			commands_copy = commands_copy->next;
		}
	}
	else
	{
		if ((*commands)->fd_in != STDIN_FILENO)
			err_assign2(close((*commands)->fd_in), EX_OSFILE, &status);
		if ((*commands)->fd_out != STDOUT_FILENO)
			err_assign2(close((*commands)->fd_out), EX_OSFILE, &status);
		*commands = (*commands)->next;
	}
	return (status);
}
