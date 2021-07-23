#include "utils.h"

char	*ft_strchr(char *str, int sep)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != sep)
	{
		i++;
	}
	if (str[i])
		return (str + i);
	return (NULL);
}
