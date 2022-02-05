#include "../includes/pipex.h"

void	er_prog_exit(void)
{
	perror("Error: ");
	exit(EXIT_FAILURE);
}
