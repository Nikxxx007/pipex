#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sysexits.h>
# include "utils.h"

# define EX_CATCHALL			1
# define EX_MISUSE_BUILTIN		2
# define EX_CMD_NOTEXEC			126
# define EX_CMD_NOTFOUND		127
# define EX_INVAL_EXIT_CODE		128
# define EX_SIGQUIT				130

# define MALLOC_ERROR -11
//	for unset and export
# define NOT_A_VALID_IDENTIFIER -12
# define HOME_NOT_SET -13
# define CD_CHDIR_ERROR -14
# define NO_SUCH_FILE -15
# define TOO_MANY_ARGS -16
# define NUMERIC_ARG_REQUIRED -17

int	perror__syntax(const char *error_token, int error_code);
int	perror__errno(const char *error_token, int error_code);
int	perror__exec(const char *error_token, int error_code);

int	perror__builtin(const char **commands, int id_of_error_arg, int error_code);

int	err_assign(int status, int *out_status);
int	err_assign2(int status, int ret_status, int *out_status);

#endif
