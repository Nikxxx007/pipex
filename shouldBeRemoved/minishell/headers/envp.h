#ifndef ENVP_H
# define ENVP_H

# include <stddef.h>
# include <stdlib.h>
# include "utils.h"
# include "error.h"

# define GOOD_RETURN 0

# define VALID_VAR 1
# define INVALID_VAR 0
# define INVALID_INDEX -1

typedef struct s_envp
{
	char	**envp_key_value[2];
	char	**envp_cpy;
}				t_envp;

# define KEY	0
# define VALUE	1

int			_fill_one_export(t_envp *ans, char *env, int i);

void		envp_clear(t_envp *exp);
t_envp		*envp_create(char **envp);
void		envp_print(t_envp *exp);
char		*envp_get_value(t_envp *exp, char *key);
int			envp_add(t_envp *exp, char *key_value);
int			envp_remove(t_envp *exp, char *key);
int			_envp_copy(t_envp *ans, char **envp, int i);
int			_copy_envp_orig(t_envp *ans, char **envp, int i);

int			envp_find_key_index(t_envp *exp, char *key);
int			get_key_from_envp_string(char *envp_str, char **rewrite);
int			get_value_from_envp_string(char *envp_str, char **rewrite);
int			ft_envplen(t_envp *env);

int			is_valid_envp_str(char *str);
int			is_valid_key(char *key);
#endif