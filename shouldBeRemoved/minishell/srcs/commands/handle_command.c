#include "commands.h"

int	is_builtin_command(char **command)
{
	return (!ft_strcmp(command[0], "echo") || !ft_strcmp(command[0], "cd")
		|| !ft_strcmp(command[0], "pwd") || !ft_strcmp(command[0], "export")
		|| !ft_strcmp(command[0], "unset") || !ft_strcmp(command[0], "env")
		|| !ft_strcmp(command[0], "exit"));
}

int	handle_command(char **command, t_envp *envp)
{
	int		status;

	if (!command || !command[0])
		status = 1;
	else if (!ft_strcmp(command[0], "echo"))
		status = builtin_echo(command);
	else if (!ft_strcmp(command[0], "cd"))
		status = builtin_cd(command, envp);
	else if (!ft_strcmp(command[0], "pwd"))
		status = builtin_pwd(command);
	else if (!ft_strcmp(command[0], "export"))
		status = builtin_export(command, envp);
	else if (!ft_strcmp(command[0], "unset"))
		status = builtin_unset(command, envp);
	else if (!ft_strcmp(command[0], "env"))
		status = builtin_env(command, envp);
	else if (!ft_strcmp(command[0], "exit"))
		status = builtin_exit(command);
	else
		status = exec_command(command, envp);
	return (status);
}
