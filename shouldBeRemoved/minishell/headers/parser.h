#ifndef PARSER_H
# define PARSER_H

# include "utils.h"
# include <unistd.h>
# include "commlist.h"
# include "envp.h"
# include "error.h"

extern int	g_last_exit_code;

// parser.c
int			parse_input(char **str, t_commlist **out_commlist,
				t_envp *envp);

// syntax_analys.c
t_operation	parser__is_oper(const char *str);
int			parser__syntax_analys(const char *str, t_operation *error_token);
void		parser__print_syntax_error(t_operation error_token);

// envp_replace
int			parser__envp_replace(char **str, t_envp *envp);
char		*replace_keys__get_value(char **envp[2], char *key,
				size_t *key_len);
size_t		replace_keys__get_new_len(char *str, char **envp[2],
				char *exit_code);
int			replace_keys__valid_key_symbol(char *str);

// parser_argv.c
char		**parser__get_argv(char **str);
char		*parser__get_word(char **str);
int			parser__get_word__check_quote(char *s,
				char *quote_flag, char *quote_var);

#endif
