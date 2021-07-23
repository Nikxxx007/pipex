#include "parser.h"

static size_t	parser__get_word__get_len(char **str);
static void		parser__get_word__copy_word(char **s, char *dst);

char	*parser__get_word(char **str)
{
	size_t	size;
	char	*out;

	size = parser__get_word__get_len(str);
	out = malloc(sizeof(char) * (size + 1));
	if (!out)
		return (NULL);
	parser__get_word__copy_word(str, out);
	out[size] = '\0';
	return (out);
}

int	parser__get_word__check_quote(char *s,
		char *quote_flag, char *quote_var)
{
	if (*quote_flag && *s == *quote_var)
	{
		*quote_flag = 0;
		*quote_var = 1;
		return (1);
	}
	else if (!*quote_flag && (*s == '\'' || *s == '\"'))
	{
		*quote_flag = 1;
		*quote_var = *s;
		return (1);
	}
	return (0);
}

static size_t	parser__get_word__get_len(char **str)
{
	size_t	size;
	char	*tmp;
	char	quote_flag;
	char	curr_quote;

	while (ft_isspace(**str))
		++(*str);
	curr_quote = 1;
	quote_flag = 0;
	size = 0;
	tmp = *str;
	while (*tmp && ((!quote_flag && !ft_isspace(*tmp)
				&& parser__is_oper(tmp) == OP_NONE) || quote_flag))
	{
		if (!parser__get_word__check_quote(tmp, &quote_flag, &curr_quote))
			++size;
		++tmp;
	}
	return (size);
}

static void	parser__get_word__copy_word(char **str, char *dest)
{
	char	quote_flag;
	char	curr_quote;

	curr_quote = 1;
	quote_flag = 0;
	while (**str && ((!quote_flag && !ft_isspace(**str)
				&& parser__is_oper(*str) == OP_NONE) || quote_flag))
	{
		if (!parser__get_word__check_quote(*str, &quote_flag, &curr_quote)
			&& **str != curr_quote)
		{
			*dest = **str;
			++dest;
		}
		++(*str);
	}
}
