#include "commands.h"
#include <unistd.h>

int	builtin_pwd(char **command)
{
	char	buf[25565];

	(void)command;
	ft_bzero(buf, 25565);
	if (getcwd(buf, 25565) == NULL)
	{
		write(2, "i dont know where are you\n", 26);
		return (1);
	}
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (EX_OK);
}
