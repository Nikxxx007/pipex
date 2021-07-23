#include "../includes/pipex.h"

static t_pipe	**pipe_singleton(void)
{
	static t_pipe	*saved_ptr;

	return (&saved_ptr);
}

t_pipe	**get_pipe_list(void)
{
	return (pipe_singleton());
}
