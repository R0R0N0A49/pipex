/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:00:50 by trebours          #+#    #+#             */
/*   Updated: 2023/11/03 17:00:52 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_count(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i += 1;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*rsl;

	i = ft_count(n);
	rsl = malloc((i + 1) * sizeof(char));
	if (!rsl)
		return (0);
	rsl[i--] = '\0';
	if (i == 10)
		n += 1;
	if (i == 10)
		rsl[i] = 1;
	if (n < 0)
	{
		rsl[0] = '-';
		n *= -1;
	}
	while (n)
	{
		rsl[i--] += (n % 10) + '0';
		n /= 10;
	}
	return (rsl);
}
