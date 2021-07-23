#include "utils.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while ((i + 1 < dstsize) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	if (dst_len > dstsize)
		return (dstsize + ft_strlen(src));
	ft_strlcpy(dst + dst_len, src, dstsize - dst_len);
	return (dst_len + ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!out)
		return (NULL);
	ft_strlcpy(out, s1, (len1 + 1));
	ft_strlcat(out, s2, (len1 + len2 + 1));
	return (out);
}

char	*ft_strdup(const char *str)
{
	char	*out;
	size_t	len;

	len = ft_strlen(str);
	out = malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	ft_strlcpy(out, str, len + 1);
	return (out);
}

//podarok [2,4) = "da"
//podarok [2, 2) = "" (empty)
char	*ft_substr_from_to(char *str, size_t begin, size_t end)
{
	char		*out;
	size_t		begin_cpy;

	if (end < begin || begin > ft_strlen(str) || end > ft_strlen(str))
		return (NULL);
	out = malloc(sizeof(char) * (end - begin + 1));
	if (!out)
		return (NULL);
	begin_cpy = begin;
	while (begin < end)
	{
		out[begin - begin_cpy] = str[begin];
		begin++;
	}
	out[begin - begin_cpy] = 0;
	return (out);
}
