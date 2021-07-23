#include "../includes/pipex.h"

char	*ft_strjoin(const char *a, const char *b)
{
	char	*n;
	int		alen;
	int		blen;
	int		i;

	if (a == NULL || b == NULL)
		return (NULL);
	alen = ft_strlen(a);
	blen = ft_strlen(b);
	n = malloc(alen + blen + 1);
	if (n == NULL)
		return (NULL);
	i = 0;
	while (*a != '\0')
		n[i++] = *a++;
	while (*b != '\0')
		n[i++] = *b++;
	n[i] = '\0';
	return (n);
}
