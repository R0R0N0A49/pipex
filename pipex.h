/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:43:54 by trebours          #+#    #+#             */
/*   Updated: 2024/02/10 10:38:38 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include "ft_printf.h"

typedef struct s_link_cmd
{
	char	**path;
	char	**cmd_1;
	char	**cmd_2;
	char	*link_1;
	char	*link_2;
	int		fd_file_1;
	int		fd_file_2;
	int		pipe[2];
}t_link_cmd;

void	pipex(t_link_cmd *vars, char *envp[]);
void	ft_initilis_struc(char **argv, char **envp, t_link_cmd *p);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	error_first_file(char *file);
void	ft_touch_file(char *file);
char	**split_modif(char *src);
void	ft_free_tab(char **src);
void	ft_close(int *p);
char	*ft_itoa(int n);

#endif