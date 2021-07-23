#include "commands.h"

int	builtin_unset(char **commands, t_envp *envp)
{
	int	i;
	int	error_code;
	int	ans;

	i = 1;
	ans = 0;
	while (commands[i])
	{
		error_code = envp_remove(envp, commands[i]);
		if (error_code != GOOD_RETURN)
		{
			ans = 1;
			perror__builtin((const char **)commands, i, NOT_A_VALID_IDENTIFIER);
		}
		i++;
	}
	return (ans);
}
