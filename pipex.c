/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:30:59 by trebours          #+#    #+#             */
/*   Updated: 2024/02/06 10:18:34 by trebours         ###   ########.fr       */
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

static void	ft_command_n(char **link_cmd_1, char ***command_1, char **envp)
{
	pid_t			tfork;

	tfork = fork();
	if (tfork == 0)
	{
		if (command_1[0][0] && execve(link_cmd_1[0], command_1[0], envp) == -1)
			perror("pipex: execve");
	}
	else
	{
		wait(NULL);
		return ;
	}
}

void	ft_pipex(t_link_cmd *seting, char **envp)
{
	int		p[2];
	pid_t	tfork;

	pipe(p);
	tfork = fork();
	if (tfork < 0)
		exit(1);
	if (tfork == 0)
	{
		dup2(seting->fd_file_1, STDIN_FILENO);
		dup2(p[1], STDOUT_FILENO);
		close(seting->fd_file_2);
		ft_command_n(&seting->link_1, &seting->cmd_1, envp);
		ft_close(p);
	}
	else
	{
		wait(NULL);
		dup2(p[0], STDIN_FILENO);
		dup2(seting->fd_file_2, STDOUT_FILENO);
		close(p[1]);
		close(seting->fd_file_1);
		ft_command_n(&seting->link_2, &seting->cmd_2, envp);
		close(p[0]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_link_cmd	cmd_and_link;

	if (argc != 5)
	{
		ft_printf
			("Pipex: argv: \"file1\" \"command1\" \"command2\" \"file2\"\n");
		return (0);
	}
	if (access(argv[1], F_OK))
		error_first_file(argv[1]);
	cmd_and_link.path = NULL;
	ft_initilis_struc(&argv[1], envp, &cmd_and_link);
	ft_pipex(&cmd_and_link, envp);
	ft_free_tab(cmd_and_link.cmd_1);
	ft_free_tab(cmd_and_link.cmd_2);
	free(cmd_and_link.link_1);
	free(cmd_and_link.link_2);
	close(cmd_and_link.fd_file_1);
	close(cmd_and_link.fd_file_2);
}
