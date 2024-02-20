/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_file_and_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:48:31 by trebours          #+#    #+#             */
/*   Updated: 2024/01/25 13:38:26 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_strlen_modif(char *src, int verif)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] != ' ' && src[i] != '\0')
		i++;
	if (verif == 0)
		return (i);
	while (src[i] != '\0')
	{
		j++;
		i++;
	}
	return (j);
}

static char	*ft_malloc_before_space(char *src)
{
	char	*result;
	int		i;

	i = 0;
	while (src[i] != ' ' && src[i] != '\0')
		i++;
	result = malloc(i + 1 * sizeof(char));
	if (!result)
		exit(1);
	i = 0;
	while (src[i] != ' ' && src[i] != '\0')
	{
		result[i] = src[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

static char	*ft_malloc_after_space(char *src)
{
	char	*result;
	int		i;
	int		j;

	i = ft_strlen_modif(src, 1);
	if (i == 0)
		return (NULL);
	result = malloc((i + 1) * sizeof(char));
	if (!result)
		exit(1);
	i = ft_strlen_modif(src, 0);
	i++;
	j = 0;
	while (src[i] != '\0')
	{
		result[j] = src[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	**split_modif(char *src)
{
	char	**result;
	int		i;

	i = 2;
	if (ft_strlen_modif(src, 0) == ft_strlen(src))
		result = malloc(i++ * sizeof(char *));
	else
		result = malloc(3 * sizeof(char *));
	if (!result)
		exit(1);
	result[0] = ft_malloc_before_space(src);
	if (i == 2)
	{
		result[1] = ft_malloc_after_space(src);
		result[2] = NULL;
	}
	else
		result[1] = NULL;
	return (result);
}
