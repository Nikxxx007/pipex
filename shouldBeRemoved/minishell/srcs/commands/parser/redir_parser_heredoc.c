#include "commands.h"
#include "signals.h"

static int		redir_left_double__fd_proc(t_commlist *iter,
					t_commlist **redir_target, int *last_fd,
					int *last_exit_code);
static void		redir_left_double__delete_n_merge(t_commlist **commands,
					t_commlist **iter);

int	redir_left_double(t_commlist **commands, int *last_exit_code)
{
	t_commlist	*iter;
	t_commlist	*redir_target;
	int			last_fd;

	*last_exit_code = EX_OK;
	last_fd = 0;
	redir_target = NULL;
	iter = *commands;
	while (iter)
	{
		if (iter->op_prev == OP_REDIR2L)
		{
			if (redir_left_double__fd_proc(iter, &redir_target,
					&last_fd, last_exit_code) != 0)
				return (-1);
			redir_left_double__delete_n_merge(commands, &iter);
		}
		else
		{
			if (iter->op_prev == OP_NONE)
				redir_target = iter;
			iter = iter->next;
		}
	}
	return (0);
}

static int	redir_left_double__fd_proc(t_commlist *iter,
				t_commlist **redir_target, int *last_fd, int *last_exit_code)
{
	if (*last_fd)
		close(*last_fd);
	*last_fd = builtin_heredoc(iter->argv[0], last_exit_code);
	if (*last_fd < 0)
		return (perror__errno(iter->argv[0], EX_OSFILE));
	if (iter->op_next != OP_REDIRL)
	{
		if (*redir_target)
		{
			if ((*redir_target)->fd_in != STDIN_FILENO)
				close((*redir_target)->fd_in);
			(*redir_target)->fd_in = *last_fd;
			if (iter->fd_out != STDOUT_FILENO)
				(*redir_target)->fd_out = iter->fd_out;
		}
		else if (iter->op_next == OP_NONE && iter->next)
			iter->next->fd_in = *last_fd;
		*last_fd = 0;
		*redir_target = NULL;
	}
	return (EX_OK);
}

static void	redir_left_double__delete_n_merge(t_commlist **commands,
				t_commlist **iter)
{
	t_commlist	*tmp;

	tmp = *iter;
	*iter = (*iter)->next;
	commlist_remove_elem(commands, tmp);
	if ((*iter) && (*iter)->op_prev == OP_NONE && (*iter)->prev)
	{
		*iter = (*iter)->prev;
		commlist_merge_two(commands, *iter);
	}
}
