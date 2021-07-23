#include "envp.h"

static int	_envp_add_new_key(t_envp *env, char *key, char *value, char *str)
{
	int	i;

	i = ft_envplen(env);
	env->envp_cpy = ft_realloc(env->envp_cpy, i * sizeof(char *),
			(i + 2) * sizeof(char *));
	env->envp_key_value[0] = ft_realloc(env->envp_key_value[0],
			i * sizeof(char *), (i + 2) * sizeof(char *));
	env->envp_key_value[1] = ft_realloc(env->envp_key_value[1],
			i * sizeof(char *), (i + 2) * sizeof(char *));
	if (!env->envp_cpy || !env->envp_key_value[0] || !env->envp_key_value[1])
	{
		free(env->envp_cpy);
		free(env->envp_key_value[0]);
		free(env->envp_key_value[1]);
		return (MALLOC_ERROR);
	}
	env->envp_key_value[0][i] = key;
	env->envp_key_value[1][i] = value;
	env->envp_cpy[i] = str;
	env->envp_key_value[0][i + 1] = NULL;
	env->envp_key_value[1][i + 1] = NULL;
	env->envp_cpy[i + 1] = NULL;
	return (GOOD_RETURN);
}

static int	_envp_add(t_envp *env, char *key, char *value, char *str)
{
	int		index;

	index = envp_find_key_index(env, key);
	if (index == -1)
		return (_envp_add_new_key(env, key, value, str));
	free(key);
	free(env->envp_key_value[1][index]);
	env->envp_key_value[1][index] = value;
	free(env->envp_cpy[index]);
	env->envp_cpy[index] = str;
	return (GOOD_RETURN);
}

int	envp_add(t_envp *env, char *str)
{
	char	*key;
	char	*value;
	char	*key_value;

	if (is_valid_envp_str(str) == INVALID_VAR)
	{
		return (NOT_A_VALID_IDENTIFIER);
	}
	key_value = ft_strdup(str);
	key = NULL;
	value = NULL;
	if (!key_value || get_key_from_envp_string(str, &key)
		|| get_value_from_envp_string(str, &value))
	{
		free(key_value);
		free(key);
		free(value);
		return (MALLOC_ERROR);
	}
	return (_envp_add(env, key, value, key_value));
}
