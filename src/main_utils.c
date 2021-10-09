#include "../includes/pipex.h"

void    er_prog_exit()
{
	perror("Error: ");
	exit(1);
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