/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogaynel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:42:26 by rogaynel          #+#    #+#             */
/*   Updated: 2022/02/13 16:24:36 by rogaynel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_mes(void)
{
	ft_putstr_fd("Incorrect nember of values\n", 2);
	ft_putstr_fd("Usage: ./pipex <file1> \
			<cmd1> <file2>\n", 1);
	exit(1);
}

int	open_type(char *filename, int type)
{
	int	ret;

	ret = 0;
	if (type == 0)
		ret = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (type == 1)
		ret = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (type == 2)
		ret = open(filename, O_RDONLY, 0777);
	if (ret == -1)
		er_prog_exit();
	return (ret);
}

void	here_doc(char *lim, int argc)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	if (argc < 6)
		print_mes();
	if (pipe(fd) == -1)
		er_prog_exit();
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (get_next_line(0, &line))
		{
			if (!(ft_strncmp(line, lim, ft_strlen(lim))))
				exit(0);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	infile;
	int	outfile;

	if (argc != 5)
		print_mes();
	if (!(ft_strncmp(argv[1], "here_doc", 8)))
	{
		i = 3;
		outfile = open_type(argv[argc - 1], 0);
		here_doc(argv[2], argc);
	}
	else
	{
		i = 2;
		outfile = open_type(argv[argc - 1], 1);
		infile = open_type(argv[1], 2);
		dup2(infile, STDIN_FILENO);
	}
	while (i < argc - 2)
		execution(argv[i++], envp);
	dup2(outfile, STDOUT_FILENO);
	cmd_ex(argv[argc - 2], envp);
}
