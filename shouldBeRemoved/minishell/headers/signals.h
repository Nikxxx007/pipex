#ifndef SIGNALS_H
# define SIGNALS_H

# include "../readline-8.1/include/readline/readline.h"
# include "../readline-8.1/include/readline/history.h"
# include <signal.h>

extern int	g_last_exit_code;

void	handler_sigint(int status);
void	handler_sigquit(int status);
void	fork_handler_sigint(int status);
void	fork_handler_sigquit(int status);

#endif