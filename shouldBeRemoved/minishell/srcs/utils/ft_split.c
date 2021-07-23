#include "utils.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	if (!*s)
		return (0);
	while (*(++s))
		if (*s == c && *(s - 1) != c)
			count++;
	if (*(s - 1) != c)
		count++;
	return (count);
}

static size_t	get_word(char **dest, char const *s, char c)
{
	size_t	len;
	int		i;

	len = 0;
	i = -1;
	while (s[++i] != c && s[i] != '\0')
		len++;
	*dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!*dest)
		return (0);
	(*dest)[len] = '\0';
	i = -1;
	while (s[++i] != c && s[i] != '\0')
		(*dest)[i] = s[i];
	while (s[++i] == c)
		;
	return (i);
}

static void	free_words(char **words, size_t size)
{
	while (size--)
		free(words[size]);
	free(words);
}

static const char	*skip_sep(char const *s, char c)
{
	while (*s == c)
		s++;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	n_o_w;
	size_t	sw;
	size_t	i;

	if (!s)
		return (ft_calloc(1, sizeof(char *)));
	n_o_w = count_words(s, c);
	words = (char **)malloc(sizeof(char *) * (n_o_w + 1));
	if (!words)
		return (NULL);
	s = skip_sep(s, c);
	i = -1;
	sw = 0;
	while (++i < n_o_w)
	{
		sw += get_word(words + i, s + sw, c);
		if (!words[i])
		{
			free_words(words, i);
			return (NULL);
		}
	}
	words[n_o_w] = NULL;
	return (words);
}
