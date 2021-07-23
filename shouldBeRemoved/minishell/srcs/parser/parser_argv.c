#include "parser.h"

static size_t	count_words(char *str);

char	**parser__get_argv(char **str)
{
	size_t		argc;
	size_t		index;
	char		**argv;

	argc = count_words(*str);
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	argv[argc] = NULL;
	index = 0;
	while (index < argc)
	{
		argv[index] = parser__get_word(str);
		if (!argv[index])
		{
			while (index--)
				free(argv[index]);
			free(argv);
			return (NULL);
		}
		index++;
	}
	return (argv);
}

static size_t	count_words(char *str)
{
	size_t	count;
	char	quote_flag;
	char	curr_quote;

	while (ft_isspace(*str))
		++str;
	quote_flag = 0;
	curr_quote = 1;
	count = 0;
	while (*str && parser__is_oper(str) == OP_NONE)
	{
		while (*str && ((!quote_flag && !ft_isspace(*str)
					&& parser__is_oper(str) == OP_NONE) || quote_flag))
		{
			parser__get_word__check_quote(str, &quote_flag, &curr_quote);
			str++;
		}
		++count;
		while (*str && ft_isspace(*str))
			str++;
	}
	return (count);
}
