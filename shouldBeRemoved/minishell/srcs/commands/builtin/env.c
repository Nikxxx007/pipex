#include "commands.h"

int	builtin_env(char **command, t_envp *exp)
{
	int	i;

	(void)command;
	i = 0;
	while (exp->envp_key_value[0][i])
	{
		if (exp->envp_key_value[1][i])
			printf("%s=%s\n", exp->envp_key_value[0][i],
				exp->envp_key_value[1][i]);
		i++;
	}
	return (0);
}
