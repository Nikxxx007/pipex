#include "../includes/pipex.h"

void	er_prog_exit(void)
{
	perror("Error: ");
	exit(EXIT_FAILURE);
}

int	get_paths(char **envp, char **command)
{
	char	**paths;

	while (ft_strnstr(*envp, "PATH", 4) == 0)
		(*envp)++;
	paths = ft_split(*envp + 5, ':');
	command[0] = cmd_maker(paths, command[0]);
	command[1] = cmd_maker(paths, command[1]);
	ar_free(paths);
	if (command[0] && command[1])
		return (1);
	return (0);
}

void	ar_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
