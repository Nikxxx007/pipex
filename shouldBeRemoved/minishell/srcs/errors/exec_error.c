#include "error.h"

int	perror__errno(const char *error_token, int error_code)
{
	const char	*error_text;

	error_text = strerror(errno);
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, error_token, ft_strlen(error_token));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error_text, ft_strlen(error_text));
	write(STDERR_FILENO, "\n", 1);
	return (error_code);
}

int	perror__exec(const char *error_token, int error_code)
{
	const char	*error_text;

	error_text = strerror(errno);
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, error_token, ft_strlen(error_token));
	write(STDERR_FILENO, ": command not found\n", 20);
	return (error_code);
}
