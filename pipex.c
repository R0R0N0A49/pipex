/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:30:59 by trebours          #+#    #+#             */
/*   Updated: 2024/02/10 10:53:41 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*rsl;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = 0;
	len_s2 = 0;
	rsl = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 2)
			* sizeof(char));
	if (rsl == 0)
		return (0);
	while (s1[len_s1])
	{
		rsl[len_s1] = s1[len_s1];
		len_s1++;
	}
	if (s1[0] != 0)
		rsl[len_s1++] = '/';
	while (s2[len_s2])
	{
		rsl[len_s1 + len_s2] = s2[len_s2];
		len_s2++;
	}
	rsl[len_s1 + len_s2] = 0;
	return (rsl);
}

void	child_process(t_link_cmd *vars, char *envp[])
{
	close(vars->pipe[0]);
	close(vars->fd_file_2);
	dup2(vars->fd_file_1, STDIN_FILENO);
	dup2(vars->pipe[1], STDOUT_FILENO);
	execve(vars->cmd_1[0], vars->cmd_1, envp);
	perror("Execve");
	ft_free_tab(vars->cmd_1);
	ft_free_tab(vars->cmd_2);
	exit(1);
}

void	second_child_process(t_link_cmd *vars, char *envp[])
{
	close (vars->pipe[1]);
	dup2(vars->pipe[0], STDIN_FILENO);
	close (vars->pipe[0]);
	dup2(vars->fd_file_2, STDOUT_FILENO);
	close (vars->fd_file_2);
	execve(vars->cmd_2[0], vars->cmd_2, envp);
	perror("Execve");
	ft_free_tab(vars->cmd_1);
	ft_free_tab(vars->cmd_2);
	exit(1);
}

void	parent_process(t_link_cmd *vars, char *envp[])
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Error : ");
		exit(1);
	}
	if (pid2 == 0)
		second_child_process(vars, envp);
	else
	{
		close(vars->fd_file_1);
		close(vars->fd_file_2);
		close (vars->pipe[1]);
		close (vars->pipe[0]);
		while (waitpid(-1, NULL, 0) != -1)
			continue ;
	}
}

void	pipex(t_link_cmd *vars, char *envp[])
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (pid1 == 0)
		child_process(vars, envp);
	else
		parent_process(vars, envp);
}
