#include "../includes/pipex.h"

char	*cmd_maker(char **paths, char *command)
{
	char	*path_start;
	char	*binary;
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(command, ' ');
	while (paths[i])
	{
		path_start = ft_strjoin(paths[i], "/");
		binary = ft_strjoin(path_start, cmd[0]);
		free(path_start);
		if (!access(binary, F_OK))
		{
			ar_free(cmd);
			return (binary);
		}
		else
			free(binary);
		i++;
	}
	return (0);
}

void	command_ex1(char **path, int *fd, char **argv, char **envp)
{
	int		file;
	char	**cmd;
	int		pid;

	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		er_prog_exit();
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(fd[1]);
	cmd = ft_split(argv[3], ' ');
	pid = fork();
	if (pid == 0)
		if (execve(path[1], cmd, envp) == -1)
			er_prog_exit();
	ar_free(cmd);
	exit(1);
}

void	command_ex(char **path, int *fd, char **argv, char **envp)
{
	int		file;
	char	**cmd;
	int		pid;
	int		i;

	i = 0;
	file = open(argv[1], O_RDONLY, 0777);
	if (file == -1)
		er_prog_exit();
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close (fd[0]);
	cmd = ft_split(argv[2], ' ');
	pid = fork();
	if (pid == 0)
		if (execve(path[0], cmd, envp) == -1)
			er_prog_exit();
	ar_free(cmd);
	exit(1);
}

void	execution(int *fd, char **path, char **argv, char **envp)
{
	pid_t	pid;

	if (pipe(fd) == -1)
		er_prog_exit();
	pid = fork();
	if (pid == -1)
		er_prog_exit();
	if (pid == 0)
		command_ex(path, fd, argv, envp);
	waitpid(pid, NULL, 0);
	pid = fork();
	if (pid == 0)
		command_ex1(path, fd, argv, envp);
	waitpid(pid, NULL, 0);
	close(fd[0]);
	close(fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	char	**files;
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!(ft_strncmp(argv[i], "", 1)))
			er_prog_exit();
		i++;
	}
	files = (char **)malloc(2 * sizeof(char *));
	files[0] = argv[2];
	files[1] = argv[3];
	if (argc != 5)
		er_prog_exit();
	else
	{
		if (!get_paths(envp, files))
			er_prog_exit();
		execution(fd, files, argv, envp);
	}
}
