#include "parser.h"

static void		replace_keys(char *str, char *dest, char **envp[2],
					char *exit_code);
static char		*replace_keys__key(char *str, char **envp[2],
					char *exit_code, size_t *key_len);
static void		replace_keys__copy_n_move(char **dest, char **src,
					int to_zero_flag);

int	parser__envp_replace(char **str, t_envp *envp)
{
	size_t	size;
	char	*out;
	char	*exit_code;

	exit_code = ft_itoa(g_last_exit_code);
	size = replace_keys__get_new_len(*str, envp->envp_key_value, exit_code);
	out = malloc(sizeof(char) * (size + 1));
	if (!out)
	{
		free(exit_code);
		return (EX_OSERR);
	}
	out[size] = '\0';
	replace_keys(*str, out, envp->envp_key_value, exit_code);
	free(exit_code);
	free(*str);
	*str = out;
	return (0);
}

char	*replace_keys__get_value(char **envp[2], char *key, size_t *key_len)
{
	size_t	index;

	*key_len = 0;
	while (key[*key_len] && !ft_isspace(key[*key_len])
		&& parser__is_oper(key) == OP_NONE
		&& key[*key_len] != '\"' && key[*key_len] != '\''
		&& key[*key_len] != '$' && key[*key_len] != '='
		&& key[*key_len] != ':')
		++(*key_len);
	index = 0;
	while (envp[KEY][index])
	{
		if (ft_strncmp(envp[KEY][index], key, *key_len) == 0
			&& !envp[KEY][index][*key_len])
			return (envp[VALUE][index]);
		index++;
	}
	return (NULL);
}

static void	replace_keys(char *str, char *dest, char **envp[2],
					char *exit_code)
{
	char	*value;
	size_t	key_len;
	int		squotes_flag;
	int		dquotes_flag;

	dquotes_flag = 0;
	squotes_flag = 0;
	while (*str)
	{
		if (!squotes_flag && *str == '\"')
			dquotes_flag = !dquotes_flag;
		else if (!dquotes_flag && *str == '\'')
			squotes_flag = !squotes_flag;
		if (!squotes_flag && replace_keys__valid_key_symbol(str))
		{
			value = replace_keys__key(str, envp, exit_code, &key_len);
			if (value)
				replace_keys__copy_n_move(&dest, &value, 1);
			str += key_len + 1;
		}
		else
			replace_keys__copy_n_move(&dest, &str, 0);
	}
}

static char	*replace_keys__key(char *str, char **envp[2],
					char *exit_code, size_t *key_len)
{
	char	*value;

	value = NULL;
	*key_len = 0;
	if (*(str + 1) == '?')
	{
		value = exit_code;
		*key_len = 1;
	}
	else if (*(str + 1))
		value = replace_keys__get_value(envp, str + 1, key_len);
	return (value);
}

static void	replace_keys__copy_n_move(char **dest, char **src,
				int to_zero_flag)
{
	if (to_zero_flag)
	{
		while (**src)
		{
			**dest = **src;
			*dest += 1;
			*src += 1;
		}
	}
	else
	{
		**dest = **src;
		*dest += 1;
		*src += 1;
	}
}
