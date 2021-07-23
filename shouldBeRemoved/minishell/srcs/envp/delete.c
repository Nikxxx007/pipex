#include "envp.h"

static int	remove_by_index(t_envp *exp, int index)
{
	free(exp->envp_cpy[index]);
	free(exp->envp_key_value[0][index]);
	free(exp->envp_key_value[1][index]);
	while (exp->envp_cpy[index])
	{
		exp->envp_cpy[index] = exp->envp_cpy[index + 1];
		exp->envp_key_value[0][index] = exp->envp_key_value[0][index + 1];
		exp->envp_key_value[1][index] = exp->envp_key_value[1][index + 1];
		index++;
	}
	return (GOOD_RETURN);
}

int	envp_remove(t_envp *exp, char *key)
{
	int	delete_index;

	if (is_valid_key(key) == INVALID_VAR)
		return (NOT_A_VALID_IDENTIFIER);
	delete_index = envp_find_key_index(exp, key);
	if (delete_index < 0)
		return (GOOD_RETURN);
	return (remove_by_index(exp, delete_index));
}
