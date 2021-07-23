#include "parser.h"

static size_t	replace_keys__get_new_len__key(char *str, char **envp[2],
					char *exit_code, size_t *key_len);

size_t	replace_keys__get_new_len(char *str, char **envp[2], char *exit_code)
{
	size_t	size;
	size_t	key_len;
	int		squotes_flag;
	int		dquotes_flag;

	squotes_flag = 0;
	dquotes_flag = 0;
	size = 0;
	while (*str)
	{
		key_len = 0;
		if (!squotes_flag && *str == '\"')
			dquotes_flag = !dquotes_flag;
		else if (!dquotes_flag && *str == '\'')
			squotes_flag = !squotes_flag;
		if (!squotes_flag && replace_keys__valid_key_symbol(str))
			size += replace_keys__get_new_len__key(str, envp,
					exit_code, &key_len);
		else
			++size;
		str += key_len + 1;
	}
	return (size);
}

static size_t	replace_keys__get_new_len__key(char *str, char **envp[2],
					char *exit_code, size_t *key_len)
{
	size_t	out_size;

	out_size = 0;
	if (*(str + 1) == '?')
	{
		out_size += ft_strlen(exit_code);
		*key_len = 1;
	}
	else if (*(str + 1))
		out_size += ft_strlen(replace_keys__get_value(envp, str + 1, key_len));
	return (out_size);
}

int	replace_keys__valid_key_symbol(char *str)
{
	return (*str == '$' && *(str + 1) && !ft_isspace(*(str + 1))
		&& *(str + 1) != '=' && *(str + 1) != '$' && (*str + 1) != ':'
		&& *(str + 1) != '\"' && *(str + 1) != '\'');
}
