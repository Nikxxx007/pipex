#include "../includes/pipex.h"

static int	exit_code_singleton(int *new_code)
{
	static int	saved_code;

	if (new_code != NULL)
		if (*new_code != 0)
			saved_code = *new_code;
	return (saved_code);
}

int	get_exit_code(void)
{
	return (exit_code_singleton(NULL));
}

int	set_exit_code(int new_code)
{
	return (exit_code_singleton(&new_code));
}
