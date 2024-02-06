/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:06:25 by trebours          #+#    #+#             */
/*   Updated: 2024/01/25 09:08:46 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* static int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (0);
} */

static int	ft_count(char const *s, char c)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (!s[i])
		return (0);
	if (s[i] == c)
	{
		if (s[ft_strlen(s) - 1] != c)
			j = 1;
		i++;
	}
	else if (s[ft_strlen(s) - 1] != c)
		j = 1;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			j++;
		i++;
	}
	return (j);
}

static size_t	ft_lenword(const char *s, char chr)
{
	size_t	i;

	i = 0;
	while (s[i] != chr && s[i])
		i++;
	return (i);
}

static char	*ft_strdup_mod(const char *s, char chr)
{
	char	*rsl;
	size_t	len_s;
	int		i;

	i = 0;
	len_s = ft_lenword(s, chr);
	rsl = malloc((len_s + 1) * sizeof(char));
	if (rsl == 0)
		return (0);
	while (s[i] && s[i] != chr)
	{
		rsl[i] = s[i];
		i++;
	}
	rsl[i] = 0;
	return (rsl);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	tab = malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			tab[j++] = ft_strdup_mod(&s[i], c);
			while (s[i] && s[i] != c)
				i++;
		}
	}
	tab[j] = 0;
	return (tab);
}
