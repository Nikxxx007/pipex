#include "../includes/pipex.h"

char	*ft_strappend(char *s, char c)
{
	char	*n;
	int		i;

	if (s == NULL)
		return (NULL);
	n = malloc(ft_strlen(s) + 2);
	if (n == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		n[i] = s[i];
		i++;
	}
	n[i++] = c;
	n[i] = '\0';
	free(s);
	return (n);
}
