/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:00:12 by trebours          #+#    #+#             */
/*   Updated: 2024/01/25 13:38:56 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_first_file(char *file)
{
	dup2(2, 1);
	ft_printf("pipex: %s: No such file in directory\n", file);
	exit(EXIT_FAILURE);
}

void	ft_close(int *p)
{
	close(p[0]);
	close(p[1]);
}

void	ft_free_tab(char **src)
{
	int	i;

	i = 0;
	while (src[i])
		free(src[i++]);
	free(src);
}
