#include "minishell.h"

int	g_last_exit_code;

char	*my_readline(void)
{
	char	*out;

	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigquit);
	printf("\e[s");
	out = readline(SHELL_NAME);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (out);
}

int	minishell(t_envp *envp)
{
	t_commlist	*commands;
	char		*input;

	g_last_exit_code = 0;
	while (1)
	{
		input = my_readline();
		if (input == NULL)
		{
			printf("\e[u%sexit\n", SHELL_NAME);
			return (g_last_exit_code);
		}
		if (*input && !g_last_exit_code)
			add_history(input);
		if (parse_input(&input, &commands, envp) == 0)
		{
			free(input);
			g_last_exit_code = command_processing(&commands, envp);
		}
		else
			free(input);
		commlist_clear(commands);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envp		*envp_copy;
	int			ret_status;

	(void)argc;
	(void)argv;
	if (!envp)
		return (0);
	rl_catch_signals = 0;
	envp_copy = envp_create(envp);
	ret_status = minishell(envp_copy);
	envp_clear(envp_copy);
	rl_clear_history();
	return (ret_status);
}
