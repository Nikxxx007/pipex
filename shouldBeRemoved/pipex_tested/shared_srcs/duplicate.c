#include "../includes/pipex.h"

char	*ft_strdup(const char *s)
{
	char	*n;
	int		i;

	if (s == NULL)
		return (NULL);
	n = malloc(ft_strlen(s) + 1);
	if (n == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
		n[i++] = *s++;
	n[i] = '\0';
	return (n);
}

char	*ft_strndup(const char *s, int len)
{
	char	*n;
	int		slen;
	int		i;

	if (s == NULL || len <= 0)
		return (NULL);
	slen = ft_strlen(s);
	if (len > slen)
		len = slen;
	n = malloc(len + 1);
	if (n == NULL)
		return (NULL);
	i = 0;
	while (i < len)
		n[i++] = *s++;
	n[i] = '\0';
	return (n);
}
