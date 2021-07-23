#include "commands.h"

int	exec_command__replace_home_dir(char **command, t_envp *envp)
{
	char	*tmp;

	if (!ft_strncmp(*command, "~/", 2))
	{
		tmp = ft_strjoin(envp_get_value(envp, "HOME"), *command + 1);
		if (!tmp)
			return (perror__errno("sys", EX_OSERR));
		free(*command);
		*command = tmp;
	}
	return (0);
}

static char	*bruteforce_binary__preprocessing(char *command, char **path_dirs,
				int *status)
{
	struct stat	buff;

	if (!*path_dirs)
	{
		if (stat(command, &buff) != 0)
			*status = ENOENT;
		return (command);
	}
	while (*command)
	{
		if (*(command++) == '/')
		{
			if (stat(command, &buff) != 0)
				*status = ENOENT;
			return (command);
		}
	}
	if (stat(command, &buff) == 0 && (buff.st_mode & S_IXUSR))
		return (command);
	return (NULL);
}

char	*bruteforce_binary__check_pathdir(char *command, char *path_dir,
			int *status)
{
	struct stat	buff;
	char		*tmp;

	tmp = ft_strjoin(path_dir, command);
	if (!tmp)
	{
		*status = perror__errno("sys", EX_OSERR);
		return (NULL);
	}
	if (stat(tmp, &buff) == 0 && (buff.st_mode & S_IXUSR))
		return (tmp);
	free(tmp);
	return (NULL);
}

char	*exec_command__bruteforce_binary(char *command, char **path_dirs,
			int *status)
{
	char		*tmp;

	*status = EX_OK;
	tmp = command;
	while (*command && ft_isspace(*command))
		command++;
	if (!*command)
		return (NULL);
	tmp = bruteforce_binary__preprocessing(command, path_dirs, status);
	if (tmp)
		return (command);
	while (*path_dirs)
	{
		tmp = bruteforce_binary__check_pathdir(command, *path_dirs, status);
		if (tmp)
			return (tmp);
		path_dirs++;
	}
	return (NULL);
}
