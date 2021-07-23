#include "utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buf;

	buf = malloc(count * size);
	if (buf)
		ft_bzero(buf, count * size);
	return (buf);
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*((unsigned char *)s++) = 0;
}

//before <= after, str1 != null, str1 will be freed
void	*ft_realloc(void *str1, size_t before, size_t after)
{
	char	*ans;
	char	*cpy;
	size_t	i;

	cpy = str1;
	if (!str1 || before > after)
		return (NULL);
	ans = malloc(after);
	if (!ans)
		return (NULL);
	i = 0;
	while (i < before)
	{
		ans[i] = cpy[i];
		i++;
	}
	free(cpy);
	return (ans);
}
