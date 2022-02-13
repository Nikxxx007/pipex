/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogaynel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:32:25 by rogaynel          #+#    #+#             */
/*   Updated: 2022/02/13 16:32:30 by rogaynel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"

# define BUFF_SIZE 1

void	er_prog_exit_b(void);
int		get_next_line(int const fd, char **line);
void	ft_free(char **str);
void	execution(char *argv, char **envp);
void	cmd_ex(char *argv, char **envp);
void	here_doc(char *lim, int argc);
int		open_type(char *filename, int type);

#endif //PIPEX_PIPIX_BONUS_H
