/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:00:12 by trebours          #+#    #+#             */
/*   Updated: 2024/01/20 09:04:33 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_first_file(char *file)
{
	dup2(2, 1);
	ft_printf("pipex: %s: No such file in directory\n", file);
	exit(EXIT_FAILURE);
}