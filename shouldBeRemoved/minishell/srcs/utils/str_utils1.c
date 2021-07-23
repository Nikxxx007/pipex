#include "utils.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		++len;
	return (len);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i] && str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int	ft_strncmp(const char *str1, const char *str2, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len - 1 && str1[i] == str2[i] && str1[i])
		i++;
	return (str1[i] - str2[i]);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\r'
		|| c == '\n' || c == '\f');
}
