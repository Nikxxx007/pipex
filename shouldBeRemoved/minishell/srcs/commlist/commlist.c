#include "commlist.h"

t_commlist	*commlist_create(char **argv)
{
	t_commlist	*out;

	out = malloc(sizeof(t_commlist));
	if (!out)
		return (NULL);
	out->prev = NULL;
	out->next = NULL;
	out->op_prev = OP_NONE;
	out->op_next = OP_NONE;
	out->fd_in = STDIN_FILENO;
	out->fd_out = STDOUT_FILENO;
	out->argv = argv;
	return (out);
}

void	commlist_push_back(t_commlist **list, t_commlist *to_add)
{
	t_commlist	*iter;

	if (!list || !to_add)
		return ;
	if (!*list)
	{
		*list = to_add;
		return ;
	}
	iter = *list;
	while (iter->next)
		iter = iter->next;
	iter->next = to_add;
	to_add->prev = iter;
}

void	commlist_push_front(t_commlist **list, t_commlist *to_add)
{
	if (!list || !to_add)
		return ;
	to_add->next = *list;
	*list = to_add;
}

void	commlist_remove_elem(t_commlist **list, t_commlist *to_delete)
{
	size_t		index;

	if (!list || !*list || !to_delete)
		return ;
	if (to_delete->prev)
		to_delete->prev->next = to_delete->next;
	if (to_delete->next)
		to_delete->next->prev = to_delete->prev;
	if (to_delete == *list)
		*list = to_delete->next;
	index = 0;
	while (to_delete->argv[index])
	{
		free(to_delete->argv[index]);
		index++;
	}
	free(to_delete->argv);
	free(to_delete);
}

void	commlist_clear(t_commlist *list)
{
	t_commlist	*tmp;
	size_t		index;

	if (!list)
		return ;
	while (list)
	{
		tmp = list;
		list = list->next;
		index = 0;
		while (tmp->argv[index++])
			free(tmp->argv[index - 1]);
		free(tmp->argv);
		free(tmp);
	}
}
