#include "commands.h"
#include <string.h>

/*
	builtin_cd function

	Если не против, я тут немного поменял структуру файла,
	чтобы было видна основная структура "функция - статические подфункции"

	Можешь прописать комментарии сюда
*/
static int	do_cd_to_user(char **command, t_envp *exp);
static int	do_cd_to_path(char **command);

int	builtin_cd(char **command, t_envp *exp)
{
	if (command[1] == NULL)
		return (do_cd_to_user(command, exp));
	return (do_cd_to_path(command));
}

static int	do_cd_to_user(char **command, t_envp *exp)
{
	char	*path;

	path = envp_get_value(exp, "HOME");
	if (!path)
		return (perror__builtin((const char **)command, 0, HOME_NOT_SET));
	if (chdir("/Users/dnicki/") == -1)
	{
		free(path);
		return (perror__errno("cd", CD_CHDIR_ERROR));
	}
	printf("%s - this dir\n", getcwd(NULL, 0));
	free(path);
	return (0);
}

static int	do_cd_to_path(char **command)
{
	if (chdir(command[1]) == -1)
		return (perror__builtin((const char **)command, 1, errno));
	return (GOOD_RETURN);
}
