/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:52:59 by trebours          #+#    #+#             */
/*   Updated: 2024/02/10 09:31:21 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_test_link_2(t_link_cmd *p)
{
	char	*verif_link_2;
	int		i;

	i = 0;
	while (p->path[i])
	{
		verif_link_2 = ft_strjoin(p->path[i], p->cmd_2[0]);
		if (access(verif_link_2, X_OK) == 0)
		{
			p->link_2 = verif_link_2;
			return ;
		}
		i++;
		free(verif_link_2);
	}
	dup2(2, 1);
	ft_printf("pipex: %s: command not found\n", p ->cmd_2[0]);
	ft_free_tab(p->cmd_1);
	ft_free_tab(p->cmd_2);
	ft_free_tab(p->path);
	free(p->link_1);
	exit(1);
}

static void	ft_test_link_1(t_link_cmd *p)
{
	char	*verif_link_1;
	int		i;

	i = 0;
	while (p->path[i])
	{
		verif_link_1 = ft_strjoin(p->path[i], p->cmd_1[0]);
		if (access(verif_link_1, X_OK) == 0)
		{
			p->link_1 = verif_link_1;
			return ;
		}
		i++;
		free(verif_link_1);
	}
	dup2(2, 1);
	ft_printf("pipex: %s: command not found\n", p ->cmd_1[0]);
	p->link_1 = NULL;
}

static void	ft_init_link(char **envp, t_link_cmd *p)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][3] == 'H')
			p->path = ft_split(&envp[i][5], ':');
		i++;
	}
	if (p->path && access(p->cmd_1[0], X_OK))
		ft_test_link_1(p);
	else
		p->link_1 = ft_strjoin("", p->cmd_1[0]);
	if (p->path && access(p->cmd_2[0], X_OK))
		ft_test_link_2(p);
	else
		p->link_2 = ft_strjoin("", p->cmd_2[0]);
	if (p->path)
		ft_free_tab(p->path);
	if ((p->link_1 && p->link_1[0] != '/')
		|| (p->link_2 && p->link_2[0] != '/'))
	{
		ft_printf("pipex: PATH: PATH does\'t exist");
		exit(1);
	}
}

void	ft_initilis_struc(char **argv, char **envp, t_link_cmd *p)
{
	p->cmd_2 = split_modif(argv[2]);
	p->cmd_1 = split_modif(argv[1]);
	p->fd_file_1 = open(argv[0], O_RDONLY);
	p->fd_file_2 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_init_link(envp, p);
	free(p->cmd_2[0]);
	free(p->cmd_1[0]);
	p->cmd_2[0] = ft_strjoin("", p->link_2);
	if (p->link_1)
		p->cmd_1[0] = ft_strjoin("", p->link_1);
	else
		p->cmd_1[0] = NULL;
}
