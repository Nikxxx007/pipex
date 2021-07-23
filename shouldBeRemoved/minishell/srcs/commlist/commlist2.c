#include "commlist.h"

static size_t	get_newargv_len(const t_commlist *iter);
static int		copy_argvs(t_commlist *iter, char **argv);
static int		clear_argv(char **argv, int size, int error_code);

int	commlist_merge_two(t_commlist **list, t_commlist *iter)
{
	char	**tmp_argv;
	size_t	index;

	if (!iter || !iter->next)
		return (0);
	tmp_argv = malloc(sizeof(char *) * get_newargv_len(iter));
	if (!tmp_argv)
		return (-1);
	if (copy_argvs(iter, tmp_argv) != 0)
		return (-2);
	index = 0;
	while (iter->argv[index])
		free(iter->argv[index++]);
	free(iter->argv);
	iter->argv = tmp_argv;
	iter->op_next = iter->next->op_next;
	commlist_remove_elem(list, iter->next);
	return (0);
}

static size_t	get_newargv_len(const t_commlist *iter)
{
	size_t	size;
	size_t	index;

	index = 0;
	while (iter->argv[index])
		index++;
	size = index;
	index = 0;
	while (iter->next->argv[index])
		index++;
	size += index + 1;
	return (size);
}

static int	copy_argvs(t_commlist *iter, char **argv)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (iter->argv[i])
	{
		argv[j] = ft_strdup(iter->argv[i]);
		if (!argv[j])
			clear_argv(argv, j, -1);
		++i;
		++j;
	}
	i = 0;
	while (iter->next->argv[i])
	{
		argv[j] = ft_strdup(iter->next->argv[i]);
		if (!argv[j])
			clear_argv(argv, j, -2);
		++i;
		++j;
	}
	argv[j] = NULL;
	return (0);
}

static int	clear_argv(char **argv, int size, int error_code)
{
	while (size-- >= 0)
		free(argv[size]);
	free(argv);
	return (error_code);
}
