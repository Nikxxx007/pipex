#include "../includes/pipex.h"

static int	count_words(const char *s, char delim)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		s += blocklen(s, delim);
		count++;
	}
	return (count);
}

static char	**free_on_error(char **split, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(split[i++]);
	free(split);
	return (NULL);
}

char	**ft_split(const char *s, char delim)
{
	char	**split;
	int		words_count;
	int		i;

	words_count = count_words(s, delim);
	split = malloc(sizeof(char *) * (words_count + 1));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < words_count)
	{
		split[i] = ft_strndup(s, wordlen(s, delim));
		if (split[i] == NULL)
			return (free_on_error(split, i));
		s += blocklen(s, delim);
		i++;
	}
	split[i] = NULL;
	return (split);
}
