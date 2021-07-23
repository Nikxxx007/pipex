#include "parser.h"

/*
	syntax_analys function

	Analys quotes and specific operations between commands.
*/
static int	quotes_analys(const char *str);
static int	operations_analys(const char *str, t_operation *error_token);

int	parser__syntax_analys(const char *str, t_operation *error_token)
{
	while (ft_isspace(*str))
		str++;
	if (!*str)
		return (EX_OK);
	*error_token = OP_NONE;
	if (quotes_analys(str) != EX_OK)
		return (EX_MISUSE_BUILTIN);
	else if (operations_analys(str, error_token) != EX_OK)
		return (EX_MISUSE_BUILTIN);
	return (EX_OK);
}

static int	quotes_analys(const char *str)
{
	char	double_q;
	char	single_q;

	single_q = 0;
	double_q = 0;
	while (*str)
	{
		if (!single_q && *str == '\"')
			double_q = !double_q;
		else if (!double_q && *str == '\'')
			single_q = !single_q;
		str++;
	}
	if (double_q || single_q)
		return (EX_MISUSE_BUILTIN);
	return (EX_OK);
}

static int	operations_redirects_analys(const char *str,
				t_operation *error_token, int is_empty);
static int	operations_pipes_analys(const char *str,
				t_operation *error_token, int is_empty);

static int	operations_analys(const char *str, t_operation *error_token)
{
	if (operations_redirects_analys(str, error_token, 0) != EX_OK
		|| operations_pipes_analys(str, error_token, 1) != EX_OK)
		return (EX_MISUSE_BUILTIN);
	return (EX_OK);
}

static int	operations_redirects_analys(const char *str,
				t_operation *error_token, int is_empty)
{
	t_operation	op;

	while (*str)
	{
		op = parser__is_oper(str);
		if (op != OP_NONE && op != OP_PIPE)
		{
			if (is_empty)
			{
				*error_token = op;
				return (EX_MISUSE_BUILTIN);
			}
			else
				is_empty = 1;
		}
		else if (!ft_isspace(*str))
			is_empty = 0;
		str += 1 + (op == OP_REDIR2L || op == OP_REDIR2R);
	}
	if (is_empty)
	{
		*error_token = OP_NONE;
		return (EX_MISUSE_BUILTIN);
	}
	return (EX_OK);
}

static int	operations_pipes_analys(const char *str,
				t_operation *error_token, int is_empty)
{
	t_operation	op;

	while (*str)
	{
		op = parser__is_oper(str);
		if (op == OP_PIPE)
		{
			if (is_empty)
			{
				*error_token = op;
				return (EX_MISUSE_BUILTIN);
			}
			else
				is_empty = 1;
		}
		else if (!ft_isspace(*str))
			is_empty = 0;
		str++;
	}
	if (is_empty)
	{
		*error_token = OP_NONE;
		return (EX_MISUSE_BUILTIN);
	}
	return (EX_OK);
}
