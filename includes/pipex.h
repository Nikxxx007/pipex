#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

void    er_prog_exit();
int		get_paths(char **envp, char **command);
char	*cmd_maker(char **paths, char *command);


# include "libft.h"

#endif
