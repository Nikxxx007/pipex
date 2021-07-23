#include "error.h"

char	*get_const_error_str(int code)
{
	if (code == MALLOC_ERROR)
		return ("malloc error");
	if (code == NOT_A_VALID_IDENTIFIER)
		return ("not a valid identifier");
	if (code == HOME_NOT_SET)
		return ("HOME not set");
	if (code == NO_SUCH_FILE)
		return ("No such file or directory");
	if (code == TOO_MANY_ARGS)
		return ("too many arguments");
	if (code == NUMERIC_ARG_REQUIRED)
		return ("numeric argument required");
	return (strerror(errno));
}

int	get_error_code_from_my_error_code(int code)
{
	(void)code;
	return (EX_CATCHALL);
}

int	perror__builtin(const char **commands, int id_of_error_arg, int error_code)
{
	char	*a;

	write(2, "minishell: ", 11);
	write(2, commands[0], ft_strlen(commands[0]));
	write(2, ": ", 2);
	if (id_of_error_arg > 0)
	{
		if (error_code == NOT_A_VALID_IDENTIFIER)
			write(2, "\'", 1);
		write(2, commands[id_of_error_arg],
			ft_strlen(commands[id_of_error_arg]));
		if (error_code == NOT_A_VALID_IDENTIFIER)
			write(2, "\'", 1);
		write(2, ": ", 2);
	}
	a = get_const_error_str(error_code);
	write(2, a, ft_strlen(a));
	write(2, "\n", 1);
	return (get_error_code_from_my_error_code(error_code));
}
