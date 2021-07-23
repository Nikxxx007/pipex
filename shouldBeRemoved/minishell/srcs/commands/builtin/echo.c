#include "commands.h"
#include "utils.h"

int	builtin_echo(char **command)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (command[i])
	{
		while (!ft_strcmp(command[i], "-n"))
		{
			++i;
			++flag;
		}
	}
	while (command[i])
	{
		write(1, command[i], ft_strlen(command[i]));
		if (command[i + 1])
			write(1, " ", 1);
		++i;
	}
	if (!flag)
		printf("\n");
	return (0);
}
