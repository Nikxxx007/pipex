#include "../includes/pipex.h"

int	ft_strncmp(const char *a, const char *b, size_t n)
{
	if (a == NULL || b == NULL)
		return (0);
	if (*a != *b || !*a || !*b || n == 1)
		return (*a - *b);
	return (ft_strncmp(a + 1, b + 1, n - 1));
}

int	ft_strcmp(const char *a, const char *b)
{
	if (a == NULL || b == NULL)
		return (0);
	if (*a != *b || !*a || !*b)
		return (*a - *b);
	return (ft_strcmp(a + 1, b + 1));
}
