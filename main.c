/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:53:19 by trebours          #+#    #+#             */
/*   Updated: 2024/02/10 10:54:20 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (pipe(cmd_and_link.pipe) == -1)
		return (-1);
	pipex(&cmd_and_link, envp);
	ft_free_tab(cmd_and_link.cmd_1);
	ft_free_tab(cmd_and_link.cmd_2);
	close(cmd_and_link.fd_file_1);
	close(cmd_and_link.fd_file_2);
	free(cmd_and_link.link_1);
	free(cmd_and_link.link_2);
}
