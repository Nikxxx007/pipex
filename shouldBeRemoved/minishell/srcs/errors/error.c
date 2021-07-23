#include "error.h"

int	err_assign(int status, int *out_status)
{
	if (*out_status != EX_OK)
		*out_status = status;
	return (status);
}

int	err_assign2(int status, int ret_status, int *out_status)
{
	if (status != EX_OK && *out_status != EX_OK)
		*out_status = ret_status;
	return (status);
}
