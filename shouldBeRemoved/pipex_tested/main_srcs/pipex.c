#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	if (ac != 5)
		return (write(1, "4 arguments must be passed to ./pipex\n", 38));
	return (main_exec(ac, av, envp));
}
