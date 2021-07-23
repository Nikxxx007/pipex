#include "../includes/pipex.h"

char	**free_string_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
	return (arr = NULL);
}
