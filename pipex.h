/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:43:54 by trebours          #+#    #+#             */
/*   Updated: 2024/01/19 11:07:59 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include "ft_printf.h"

void	error_first_file(char *file);
void	ft_touch_file(char *file);
void	ft_rm_file(char *file);

#endif