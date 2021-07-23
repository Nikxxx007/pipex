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

static void	execute_readfile_cmd(int readfile_fd, char *cmd, char **envp)
{
	int		out_fd;
	char	**args;
	pid_t	pid;

	args = ft_split(cmd, ' ');
	out_fd = get_fd_from_pipe_list();
	pid = fork();
	if (pid == 0)
	{
		dup2(readfile_fd, 0);
		dup2(out_fd, 1);
		close(out_fd);
		close(readfile_fd);
		execve(args[0], args, envp);
		exit(127);
	}
	close(out_fd);
	free_string_arr(args);
	append_pid(get_pid_list(), pid);
}

static void	execute_inner_cmds(int cmd_count, char **cmd, char **envp)
{
	int		in_fd;
	int		out_fd;
	char	**args;
	pid_t	pid;

	if (cmd_count == 0)
		return ;
	args = ft_split(*cmd, ' ');
	in_fd = get_fd_from_pipe_list();
	out_fd = get_fd_from_pipe_list();
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
	execute_inner_cmds(cmd_count - 1, cmd + 1, envp);
}

static void	execute_writefile_cmd(int writefile_fd, char *cmd, char **envp)
{
	int		in_fd;
	char	**args;
	pid_t	pid;

	args = ft_split(cmd, ' ');
	in_fd = get_fd_from_pipe_list();
	pid = fork();
	if (pid == 0)
	{
		dup2(in_fd, 0);
		dup2(writefile_fd, 1);
		close(in_fd);
		close(writefile_fd);
		execve(args[0], args, envp);
		exit(127);
	}
	close(in_fd);
	free_string_arr(args);
	append_pid(get_pid_list(), pid);
}

int	main_exec_bonus(int ac, char **av, char **envp)
{
	int	file_fd[2];

	if (handle_cmds(av + 2, ac - 3, envp) != 0)
		return (2);
	if (handle_files(file_fd, ac, av) != 0)
		return (1);
	create_pipes(ac - 4);
	execute_readfile_cmd(file_fd[0], av[2], envp);
	execute_inner_cmds(ac - 5, av + 2, envp);
	execute_writefile_cmd(file_fd[1], av[ac - 2], envp);
	wait_for_all_procs();
	close(file_fd[0]);
	close(file_fd[1]);
	free_pid_list();
	return (get_exit_code());
}
