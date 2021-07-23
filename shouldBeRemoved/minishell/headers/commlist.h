#ifndef COMMLIST_H
# define COMMLIST_H

# include <stdlib.h>
# include <unistd.h>
# include "utils.h"

typedef unsigned char	t_operation;
# define OP_NONE		0
# define OP_PIPE		1
# define OP_REDIRL		2
# define OP_REDIRR		3
# define OP_REDIR2L 	4
# define OP_REDIR2R 	5

typedef struct s_commlist
{
	struct s_commlist	*prev;
	struct s_commlist	*next;
	t_operation			op_prev;
	t_operation			op_next;
	char				**argv;
	int					fd_in;
	int					fd_out;
}				t_commlist;

t_commlist	*commlist_create(char **argv);

void		commlist_push_back(t_commlist **list, t_commlist *to_add);
void		commlist_push_front(t_commlist **list, t_commlist *to_add);

int			commlist_merge_two(t_commlist **list, t_commlist *iter);

void		commlist_remove_elem(t_commlist **list, t_commlist *to_delete);
void		commlist_clear(t_commlist *list);

void		commlist_print(t_commlist *lst);

#endif