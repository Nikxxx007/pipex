#include "parser.h"

t_operation	parser__is_oper(const char *str)
{
	t_operation	out;

	out = OP_NONE;
	if (*str == '|')
		out = OP_PIPE;
	else if (*str == '<')
	{
		if (str[1] == '<')
			out = OP_REDIR2L;
		else
			out = OP_REDIRL;
	}
	else if (*str == '>')
	{
		if (str[1] == '>')
			out = OP_REDIR2R;
		else
			out = OP_REDIRR;
	}
	return (out);
}

void	parser__print_syntax_error(t_operation error_token)
{
	const char	*str_token;

	if (error_token == OP_NONE)
		str_token = "newline";
	else if (error_token == OP_PIPE)
		str_token = "|";
	else if (error_token == OP_REDIRL)
		str_token = "<";
	else if (error_token == OP_REDIRR)
		str_token = ">";
	else if (error_token == OP_REDIR2L)
		str_token = "<<";
	else if (error_token == OP_REDIR2R)
		str_token = ">>";
	perror__syntax(str_token, 0);
}
