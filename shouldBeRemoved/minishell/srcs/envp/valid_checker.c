#include "envp.h"

int	is_valid_key(char *key)
{
	int	i;

	i = 1;
	if ((!ft_isalpha(key[0]) && key[0] != '_') || !key[0])
		return (INVALID_VAR);
	while (key[i])
	{
		if (!ft_isalpha(key[i]) && key[i] != '_' && !ft_isdigit(key[i]))
			return (INVALID_VAR);
		i++;
	}
	return (VALID_VAR);
}

int	is_valid_envp_str(char *str)
{
	int	i;

	i = 1;
	if ((!ft_isalpha(str[0]) && str[0] != '_') || !str[0])
		return (INVALID_VAR);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]))
			return (INVALID_VAR);
		i++;
	}
	return (VALID_VAR);
}
