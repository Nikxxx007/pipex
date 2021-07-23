#include "parser.h"

static int		fill_commlist(char *str, t_commlist **commlist);
static int		fill_commlist__push_elem(char **str, t_commlist **commlist,
					t_operation oper);
static int		fill_commlist__push_wrd_elem(char **str, t_commlist **commlist,
					t_operation oper);
static void		skip_spaces(char **str);

int	parse_input(char **str, t_commlist **out_commlist,
		t_envp *envp)
{
	t_operation	error_token;
	int			status;

	*out_commlist = NULL;
	if (parser__syntax_analys(*str, &error_token) != EX_OK)
	{
		parser__print_syntax_error(error_token);
		g_last_exit_code = 2;
		return (EX_MISUSE_BUILTIN);
	}
	status = parser__envp_replace(str, envp);
	if (status != 0)
		return (status);
	*out_commlist = NULL;
	status = fill_commlist(*str, out_commlist);
	if (status != 0)
		return (status);
	return (EX_OK);
}

static int	fill_commlist(char *str, t_commlist **commlist)
{
	t_operation	op;
	int			status;

	skip_spaces(&str);
	while (*str)
	{
		op = parser__is_oper(str);
		if (op != OP_NONE)
			str += 1 + (op == OP_REDIR2L || op == OP_REDIR2R);
		if (op == OP_NONE || op == OP_PIPE)
		{
			status = fill_commlist__push_elem(&str, commlist, op);
			if (status != 0)
				return (status);
		}
		else if (op != OP_NONE && op != OP_PIPE)
		{
			status = fill_commlist__push_wrd_elem(&str, commlist, op);
			if (status != 0)
				return (status);
		}
		skip_spaces(&str);
	}
	return (EX_OK);
}

static int	fill_commlist__push_wrd_elem(char **str, t_commlist **commlist,
					t_operation oper)
{
	t_commlist	*tmp;
	char		**argv;

	argv = malloc(sizeof(char *) * 2);
	if (!argv)
		return (perror__errno("sys", EX_OSERR));
	argv[1] = NULL;
	argv[0] = parser__get_word(str);
	if (!*argv)
		return (perror__errno("sys", EX_OSERR));
	tmp = commlist_create(argv);
	if (!tmp)
		return (perror__errno("sys", EX_OSERR));
	commlist_push_back(commlist, tmp);
	tmp->op_prev = oper;
	if (tmp->prev)
		tmp->prev->op_next = oper;
	return (0);
}

static int	fill_commlist__push_elem(char **str, t_commlist **commlist,
				t_operation oper)
{
	t_commlist	*tmp;
	char		**argv;

	argv = parser__get_argv(str);
	if (!argv)
		return (perror__errno("sys", EX_OSERR));
	tmp = commlist_create(argv);
	if (!tmp)
		return (perror__errno("sys", EX_OSERR));
	commlist_push_back(commlist, tmp);
	tmp->op_prev = oper;
	if (tmp->prev)
		tmp->prev->op_next = oper;
	return (0);
}

static void	skip_spaces(char **str)
{
	while (ft_isspace(**str))
		*str += 1;
}
