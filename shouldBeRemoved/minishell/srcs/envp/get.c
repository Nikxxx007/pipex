#include "envp.h"

int	envp_find_key_index(t_envp *exp, char *key)
{
	int	i;

	i = 0;
	while (exp->envp_cpy[i])
	{
		if (!ft_strcmp(exp->envp_key_value[0][i], key))
			return (i);
		i++;
	}
	return (-1);
}

char	*envp_get_value(t_envp *exp, char *key)
{
	int	i;

	i = 0;
	while (exp->envp_key_value[0][i])
	{
		if (!ft_strcmp(key, exp->envp_key_value[0][i]))
			return (ft_strdup(exp->envp_key_value[1][i]));
		++i;
	}
	return (NULL);
}
