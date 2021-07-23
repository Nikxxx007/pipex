#include "envp.h"
#include <stdio.h>

t_envp	*envp_create(char **envp)
{
	int			i;
	t_envp		*ans;

	i = 0;
	while (envp[i])
		i++;
	ans = ft_calloc(1, sizeof(t_envp));
	if (!ans)
		return (NULL);
	ans->envp_key_value[0] = ft_calloc(sizeof(char *), (i + 1));
	ans->envp_key_value[1] = ft_calloc(sizeof(char *), (i + 1));
	ans->envp_cpy = ft_calloc(sizeof(char *), (i + 1));
	if (!ans->envp_key_value[0] || !ans->envp_key_value[1] || !ans->envp_cpy
		|| _envp_copy(ans, envp, i) || _copy_envp_orig(ans, envp, i))
	{
		envp_clear(ans);
		return (NULL);
	}
	return (ans);
}

void	envp_clear(t_envp *exp)
{
	int	i;

	if (!exp)
		return ;
	i = 0;
	while (exp && exp->envp_key_value[0] && exp->envp_cpy
		&& exp->envp_key_value[1] && exp->envp_key_value[0][i])
	{
		free(exp->envp_key_value[0][i]);
		free(exp->envp_key_value[1][i]);
		free(exp->envp_cpy[i]);
		i++;
	}
	if (exp && exp->envp_key_value[0] && exp->envp_cpy
		&& exp->envp_key_value[1])
	{
		free(exp->envp_key_value[0][i]);
		free(exp->envp_key_value[1][i]);
		free(exp->envp_cpy[i]);
	}
	free(exp->envp_key_value[0]);
	free(exp->envp_key_value[1]);
	free(exp->envp_cpy);
	free(exp);
}

void	envp_print(t_envp *exp)
{
	int	i;

	i = 0;
	while (exp->envp_key_value[0][i])
	{
		printf("%s = >>> %s <<<\n", exp->envp_key_value[0][i],
			exp->envp_key_value[1][i]);
		printf("[ %s ]\n\n", exp->envp_cpy[i]);
		i++;
	}
}

int	ft_envplen(t_envp *env)
{
	int	i;

	i = 0;
	while (env->envp_cpy[i])
		i++;
	return (i);
}
