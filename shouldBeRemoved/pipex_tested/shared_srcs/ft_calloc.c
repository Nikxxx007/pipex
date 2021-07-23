#include "../includes/pipex.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	if (b == NULL || len == 0)
		return (b);
	*(char *)b = c;
	return (ft_memset(b + 1, c, len - 1));
}

void	*ft_calloc(size_t size, size_t count)
{
	void	*ptr;

	if (size == 0 || count == 0)
		return (NULL);
	ptr = malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, size * count);
	return (ptr);
}
