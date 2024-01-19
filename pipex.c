/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:30:59 by trebours          #+#    #+#             */
/*   Updated: 2024/01/18 13:58:55 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	ft_touch_file(char *file)
{
	char *const	touch[] = {"touch", file, NULL};
	int			fd;
	pid_t		tfork;

	tfork = fork();
	if (tfork == 0)
	{
		if (execve("/bin/touch", touch, NULL) == -1)
			perror("execve");	
	}
	else
	{
		wait(NULL);
		fd = open(file, O_WRONLY);
		if (fd == -1)
		{
			// dup2(2, 1);
			// ft_printf("bash: %s:file cannot be created\n", file);
			exit(EXIT_FAILURE);
		}
		return (fd);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int fd[2];
	
	if (argc < 5)
		return (0);
	fd[0] = open(argv[1], O_RDWR);
	if (fd[0] <= 0)
	{
		dup2(2, 1);
		ft_printf("bash: %s: No such file in directory\n", argv[1]);
		return (0);
	}
	fd[1] = open(argv[argc - 1], O_WRONLY);
	if (fd[1] <= 0)
	{
		fd[1] = ft_touch_file(argv[argc - 1]);
		if (fd[1] < 0)
			return (0);
		dup2(fd[1], 1);
	}
	ft_printf("good\n");
	close(fd[0]);
	close(fd[1]);
}
