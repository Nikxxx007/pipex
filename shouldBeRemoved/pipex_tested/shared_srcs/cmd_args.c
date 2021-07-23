#include "../includes/pipex.h"

static int	free_on_error(char *cmd, char *args, char **paths)
{
	free(cmd);
	free(args);
	free_string_arr(paths);
	return (1);
}

static char	**get_paths_with_slash(char **paths)
{
	char	*tmp;
	int		i;

	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
	return (paths);
}

static char	**get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			return (get_paths_with_slash(ft_split(envp[i] + 5, ':')));
		i++;
	}
	return (NULL);
}

static int	append_path_and_access(char **cmd, char **paths)
{
	char	*cmd_with_path;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		cmd_with_path = ft_strjoin(paths[i], *cmd);
		if (access(cmd_with_path, X_OK) == 0)
		{
			free(*cmd);
			*cmd = cmd_with_path;
			return (0);
		}
		free(cmd_with_path);
		i++;
	}
	write(1, *cmd, ft_strlen(*cmd));
	write(1, ": command not found\n", 20);
	return (1);
}

int	handle_cmds(char **cmds, int cmd_count, char **envp)
{
	char	*cmd;
	char	*args;
	char	**paths;
	int		block_len;
	int		i;

	paths = get_paths(envp);
	if (paths == NULL)
		return (1);
	i = 0;
	while (i < cmd_count)
	{
		cmd = ft_strndup(cmds[i], wordlen(cmds[i], ' '));
		block_len = blocklen(cmds[i], ' ');
		block_len -= block_len != ft_strlen(cmds[i]);
		args = ft_strdup(cmds[i] + block_len);
		if (access(cmd, X_OK) != 0 && append_path_and_access(&cmd, paths) != 0)
			return (free_on_error(cmd, args, paths));
		cmds[i] = ft_strjoin(cmd, args);
		free(cmd);
		free(args);
		i++;
	}
	free_string_arr(paths);
	return (0);
}
