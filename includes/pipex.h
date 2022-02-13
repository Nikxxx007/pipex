/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogaynel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:59:42 by rogaynel          #+#    #+#             */
/*   Updated: 2022/02/13 14:59:44 by rogaynel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"

void	er_prog_exit(void);
char	*find_path(char *cmd, char **envp);
void	cmd_ex(char *argv, char **envp);
int		get_next_line(int const fd, char **line);
void	execution(char *argv, char **envp);

#endif
