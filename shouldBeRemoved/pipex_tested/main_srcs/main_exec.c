#include "../includes/pipex.h"

static int	handle_files(int file_fd[2], int ac, char **av)
{
	file_fd[0] = open(av[1], O_RDONLY);
	if (file_fd[0] == -1)
		return (write(1, "Couldn't open file to read from\n", 32));
	file_fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (file_fd[1] == -1)
		return (write(1, "Couldn't open file to write to\n", 31));
	return (0);
}

static void	execute_cmd(int in_fd, int out_fd, char *cmd, char **envp)
{
	char	**args;
	pid_t	pid;

	args = ft_split(cmd, ' ');
	pid = fork();
	if (pid == 0)
	{
		dup2(in_fd, 0);
		dup2(out_fd, 1);
		close(in_fd);
		close(out_fd);
		execve(args[0], args, envp);
		exit(127);
	}
	close(in_fd);
	close(out_fd);
	free_string_arr(args);
	append_pid(get_pid_list(), pid);
}

int	main_exec(int ac, char **av, char **envp)
{
	int	file_fd[2];
	int	pipe_fd[2];

	if (handle_cmds(av + 2, ac - 3, envp) != 0)
		return (2);
	if (handle_files(file_fd, ac, av) != 0)
		return (1);
	pipe(pipe_fd);
	execute_cmd(file_fd[0], pipe_fd[1], av[2], envp);
	execute_cmd(pipe_fd[0], file_fd[1], av[3], envp);
	wait_for_all_procs();
	free_pid_list();
	return (get_exit_code());
}
