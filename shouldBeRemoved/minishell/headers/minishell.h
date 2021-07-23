#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>

# include "signals.h"
# include "envp.h"
# include "commands.h"
# include "utils.h"
# include "parser.h"

# define SHELL_NAME2 "\x1b[1;32mMem4AgainShell:\x1b[0m "
# define SHELL_NAME "KPACUBO$ "

#endif