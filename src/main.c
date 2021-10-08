#include "../includes/pipex.h"

char *cmd_maker(char **paths, char *command)
{
	char	*path_start;
	char	*binary;
	char 	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(command, ' ');
	while (paths[i])
	{
		path_start = ft_strjoin(paths[i], "/");
		binary = ft_strjoin(path_start, cmd[0]);
		free(path_start);
		if (!access(binary, F_OK))
			return (binary);
		i++;
	}
	return (0);
}

int	get_paths(char **envp, char **command)
{
	char	**paths;

	while (ft_strnstr(*envp, "PATH", 4) == 0)
		(*envp)++;
	paths = ft_split(*envp + 5, ':');

	if (cmd_maker(paths, command[0]) && cmd_maker(paths, command[1]))//TODO check correct values return from command_maker()
	{
		command[0] = cmd_maker(paths, command[0]);
		command[1] = cmd_maker(paths, command[1]);
		return (1);
	}
	return (0);
	// TODO finish commands
}
void command_ex1(char **path, int *fd, char **argv, char **envp)
{
	int file;
	char **cmd;

	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		er_prog_exit();
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(fd[1]);
	cmd = ft_split(argv[3], ' ');
	if (execve(path[1], cmd, envp) == -1)
		er_prog_exit();
}

void command_ex(char **path, int *fd, char **argv, char **envp)
{
	int		file;
	char	**cmd;

		file = open(argv[1], O_RDONLY, 0777);
		if (file == -1)
			er_prog_exit();
		dup2(fd[1], STDOUT_FILENO);
		dup2(file, STDIN_FILENO);
		close (fd[0]);
		cmd = ft_split(argv[2], ' ');
		if (execve(path[0], cmd, envp) == -1)
			er_prog_exit();
}

void execution(int *fd, char **path, char **argv, char **envp)
{
	pid_t pid;

	if (pipe(fd) == -1)
		er_prog_exit();
	pid = fork();
	if (pid == -1)
		er_prog_exit();
	if (pid == 0)
		command_ex(path, fd, argv, envp);
	waitpid(pid, NULL, 0);
	command_ex1(path, fd, argv, envp); //TODO function for main process(correct in values)
	close(fd[0]);
	close(fd[1]);
}

int    main(int argc, char **argv, char **envp)
{
	int 	fd[2]; //fd[0] - read, [1] - write
	char	*files[2]; //file[0] - in, [2] - out

	files[0] = argv[2];
	files[1] = argv[3];
    if (argc != 5)
        er_prog_exit();
    else
    {
		if (!get_paths(envp, files))
			er_prog_exit();//TODO free paths
		execution(fd, files, argv, envp);
	}
} // TODO check for leaks and free all splits

