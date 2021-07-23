#include "../includes/pipex.h"

static t_pipe	*new_pipe_node(int fd)
{
	t_pipe	*node;

	node = malloc(sizeof(t_pipe));
	node->fd = fd;
	node->next = NULL;
	return (node);
}

static void	append_pipe(t_pipe **head, int new_fd[2])
{
	if (*head == NULL)
	{
		*head = new_pipe_node(new_fd[1]);
		(*head)->next = new_pipe_node(new_fd[0]);
		return ;
	}
	append_pipe(&((*head)->next), new_fd);
}

static void	del_pipe_node(t_pipe **node)
{
	t_pipe	*tmp;

	tmp = (*node)->next;
	free(*node);
	*node = tmp;
}

void	create_pipes(int cmd_count)
{
	int	fd[2];

	if (cmd_count == 0)
		return ;
	pipe(fd);
	append_pipe(get_pipe_list(), fd);
	create_pipes(cmd_count - 1);
}

int	get_fd_from_pipe_list(void)
{
	t_pipe	**head;
	int		fd;

	head = get_pipe_list();
	if (*head == NULL)
		return (-1);
	fd = (*head)->fd;
	del_pipe_node(head);
	return (fd);
}
