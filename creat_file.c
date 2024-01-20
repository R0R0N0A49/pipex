/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:48:31 by trebours          #+#    #+#             */
/*   Updated: 2024/01/20 09:39:39 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_touch_file(char *file)
{
	char *const	touch[] = {"touch", file, NULL};
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
		return ;
	}
}

void	ft_rm_file(char *file)
{
	char *const	rm[] = {"rm", file, NULL};
	pid_t		tfork;

	tfork = fork();
	if (tfork == 0)
	{
		if (execve("/bin/rm", rm, NULL) == -1)
			perror("execve");
	}
	else
	{
		wait(NULL);
		return ;
	}
}
