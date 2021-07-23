#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	if (ac < 5)
		return (write(1, "At least 4 arguments must \
					be passed to ./pipex\n", 47));
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		return (heredoc_exec(ac, av, envp));
	return (main_exec_bonus(ac, av, envp));
}
