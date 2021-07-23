#include "error.h"

int	perror__syntax(const char *error_token, int error_code)
{
	write(STDERR_FILENO,
		"minishell: syntax error near unexpected token `",
		47);
	write(STDERR_FILENO, error_token, ft_strlen(error_token));
	write(STDERR_FILENO, "\'\n", 2);
	return (error_code);
}
