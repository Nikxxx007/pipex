#ifndef COMMANDS_H
# define COMMANDS_H

# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

# include "commlist.h"
# include "envp.h"
# include "utils.h"
# include "error.h"

extern int	g_last_exit_code;

int		command_processing(t_commlist **commands, t_envp *envp);
int		commands__pipe_parser(t_commlist *commands);

int		commands__redir_parser(t_commlist **commands);
int		redir_left_double(t_commlist **commands, int *last_exit_code);
int		redir_left_uno(t_commlist **commands);
int		redir_right_all(t_commlist **commands);

int		exec_all_processes(t_commlist *commands, t_envp *envp, int *pids);
int		is_builtin_command(char **command);
int		handle_command(char **command, t_envp *envp);

// builtin commands
int		builtin_echo(char **command);
int		builtin_cd(char **command, t_envp *envp);
int		builtin_pwd(char **command);
int		builtin_export(char **command, t_envp *envp);
int		builtin_unset(char **command, t_envp *envp);
int		builtin_env(char **command, t_envp *envp);
int		builtin_exit(char **command);
int		builtin_heredoc(char *command, int *status);
// exec commands
int		exec_command(char **argv, t_envp *envp);
int		exec_command__replace_home_dir(char **command, t_envp *envp);
char	*exec_command__bruteforce_binary(char *command, char **path_dirs,
			int *status);

#endif
