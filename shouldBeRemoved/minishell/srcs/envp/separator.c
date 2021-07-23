#include "envp.h"

int	get_key_from_envp_string(char *envp_str, char **rewrite)
{
	int	i;

	i = 0;
	while (envp_str[i] && envp_str[i] != '=')
		i++;
	*rewrite = malloc(sizeof(char) * (i + 1));
	if (!*rewrite)
		return (MALLOC_ERROR);
	i = 0;
	while (envp_str[i] && envp_str[i] != '=')
	{
		(*rewrite)[i] = envp_str[i];
		i++;
	}
	(*rewrite)[i] = 0;
	return (GOOD_RETURN);
}

int	get_value_from_envp_string(char *envp_str, char **rewrite)
{
	int	i;

	i = 0;
	while (envp_str[i] && envp_str[i] != '=')
		i++;
	if (!envp_str[i])
	{
		*rewrite = NULL;
		return (GOOD_RETURN);
	}
	*rewrite = ft_strdup(envp_str + (i + 1));
	if (!(*rewrite))
		return (MALLOC_ERROR);
	return (GOOD_RETURN);
}
