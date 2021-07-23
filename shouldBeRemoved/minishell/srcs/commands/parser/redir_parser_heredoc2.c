#include "commands.h"
#include "minishell.h"

static void		builtin_heredoc_exec(char *command, int fd_out);

static void	handler_in_heredoc(int status)
{
	if (status == 2)
	{
		printf("\n");
		readline(NULL);
		exit(EX_CATCHALL);
	}
}

int	builtin_heredoc(char *command, int *status)
{
	int	pipe_fds[2];
	int	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(pipe_fds) < 0)
		return (perror__errno("sys", EX_OSERR));
	pid = fork();
	if (pid < 0)
		return (perror__errno("sys", EX_OSERR));
	else if (pid == 0)
	{
		close(pipe_fds[0]);
		builtin_heredoc_exec(command, pipe_fds[1]);
		exit(0);
	}
	close(pipe_fds[1]);
	waitpid(pid, status, 0);
	*status = WEXITSTATUS(*status);
	return (pipe_fds[0]);
}

static void	builtin_heredoc_exec(char *command, int fd_out)
{
	char	*input;

	input = NULL;
	signal(SIGINT, handler_in_heredoc);
	signal(SIGQUIT, handler_in_heredoc);
	while (1)
	{
		printf("\e[s");
		input = readline("> ");
		if (!input || !ft_strcmp(input, command))
		{
			free(input);
			break ;
		}
		write(fd_out, input, ft_strlen(input));
		write(fd_out, "\n", 1);
		free(input);
	}
	free(input);
	close(fd_out);
}
