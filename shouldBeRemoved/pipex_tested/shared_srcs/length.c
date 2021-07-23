#include "../includes/pipex.h"

int	wordlen(const char *s, char delim)
{
	if (s == NULL || *s == '\0' || *s == delim)
		return (0);
	return (1 + wordlen(s + 1, delim));
}

int	blocklen(const char *s, char delim)
{
	int	len;

	len = wordlen(s, delim);
	while (s[len] == delim && s[len] != '\0')
		len++;
	return (len);
}

int	ft_strlen(const char *s)
{
	if (s == NULL || *s == '\0')
		return (0);
	return (1 + ft_strlen(s + 1));
}
