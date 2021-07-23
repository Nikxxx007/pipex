#include "utils.h"

static size_t	count_words(char const *s, int (*sep_cmp)(char))
{
	size_t	count;

	count = 0;
	if (!*s)
		return (0);
	while (*(++s))
		if (sep_cmp(*s) && !sep_cmp(*(s - 1)))
			count++;
	if (!sep_cmp(*(s - 1)))
		count++;
	return (count);
}

static size_t	get_word(char **dest, char const *s,
							int (*sep_cmp)(char), const char *tail)
{
	size_t	len;
	size_t	tail_len;
	int		i;
	int		j;

	len = 0;
	i = -1;
	while (s[++i] != '\0' && !sep_cmp(s[i]))
		len++;
	tail_len = ft_strlen(tail);
	*dest = (char *)malloc(sizeof(char) * (len + tail_len + 1));
	if (!*dest)
		return (0);
	(*dest)[len + tail_len] = '\0';
	j = -1;
	while (tail[++j])
		(*dest)[len + j] = tail[j];
	i = -1;
	while (s[++i] != '\0' && !sep_cmp(s[i]))
		(*dest)[i] = s[i];
	while (s[i] != '\0' && sep_cmp(s[i]))
		++i;
	return (i);
}

static void	free_words(char **words, size_t size)
{
	while (size--)
		free(words[size]);
	free(words);
}

static const char	*skip_sep(char const *s, int (*cmp)(char))
{
	while (cmp(*s))
		s++;
	return (s);
}

/*
	ft_smart_split function
	Split src string by separator (defined inside cmp function) and adding tail
	to each of separeted strings.
	Params:
const char*		s		-- src string to split
int	(*)(char)	sep_cmp	-- comparator for sep, returns 1 or 0 (i.e. isspace)
const char*		tail	-- null terminated string, that will be add 
							to each of words
	Returns:
char**			array	-- array of ptrs to splitted allocated words,
							last pointer is NULL.
*/
char	**ft_smart_split(const char *s, int (*sep_cmp)(char), const char *tail)
{
	char	**words;
	size_t	n_o_w;
	size_t	sw;
	size_t	i;

	if (!s)
		return (ft_calloc(1, sizeof(char *)));
	n_o_w = count_words(s, sep_cmp);
	words = (char **)malloc(sizeof(char *) * (n_o_w + 1));
	if (!words)
		return (NULL);
	s = skip_sep(s, sep_cmp);
	i = -1;
	sw = 0;
	while (++i < n_o_w)
	{
		sw += get_word(words + i, s + sw, sep_cmp, tail);
		if (!words[i])
		{
			free_words(words, i);
			return (NULL);
		}
	}
	words[n_o_w] = NULL;
	return (words);
}
