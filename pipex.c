/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:30:59 by trebours          #+#    #+#             */
/*   Updated: 2024/01/20 12:30:59 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_malloc_before_space(char *src)
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

int	ft_strlen_modif(char *src, int verif)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] != ' ' && src[i] != '\0')
		i++;
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

char	*ft_malloc_after_space(char *src)
{
	char	*result;
	int		i;
	int		j;

	i = ft_strlen_modif(src, 1);
	if (i == 0)
		return (NULL);
	result = malloc((i + 1)* sizeof(char));
	if (!result)
		exit(1);
	i = ft_strlen_modif(src, 0);
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

	result = malloc(3 * sizeof(char *));
	if (!result)
		exit(1);
	result[0] = ft_malloc_before_space(src);
	result[1] = ft_malloc_after_space(src);
	result[2] = NULL;
	return (result);
}

void	ft_free_tab(char **src)
{
	int	i;

	i = 0;
	while (src[i])
		free(src[i++]);
	free(src);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*rsl;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = 0;
	len_s2 = 0;
	rsl = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1)
			* sizeof(char));
	if (rsl == 0)
		return (0);
	while (s2[len_s2] || s1[len_s1])
	{
		if (s1[len_s1] && len_s2 == 0)
		{
			rsl[len_s1] = s1[len_s1];
			len_s1++;
		}
		else
		{
			rsl[len_s1 + len_s2] = s2[len_s2];
			len_s2++;
		}
	}
	rsl[len_s1 + len_s2] = 0;
	return (rsl);
}

void	ft_command_n(char *cmd)
{
	char **const	command = split_modif(cmd);
	char			*link_cmd;
	pid_t			tfork;

	link_cmd = ft_strjoin("/bin/", command[0]);
	tfork = fork();
	if (tfork == 0)
	{
		if (execve(link_cmd, command, NULL) == -1)
			perror("pipex: execve");
	}
	else
	{
		wait(NULL);
		ft_free_tab((char **)command);
		free(link_cmd);
		return ;
	}
}

void	ft_pipex(int *fd, char **cmd)
{
	int	p[2];
	(void)fd;

	if (pipe(p) < 0)
		exit(1);
	dup2(fd[0], 0);
	dup2(p[1], 1);
	// close(p[1]);
	ft_command_n(cmd[0]);
	dup2(p[0], 0);
	// close(p[0]);
	dup2(fd[1], 1);
	ft_printf("test");
	ft_command_n(cmd[1]);
}

int	main(int argc, char **argv)
{
	int	fd[2];

	if (argc < 5)
		return (0);
	if (access(argv[1], F_OK))
		error_first_file(argv[1]);
	if (access(argv[argc - 1], F_OK) == 0)
		ft_rm_file(argv[argc - 1]);
	ft_touch_file(argv[argc - 1]);
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[argc - 1], O_WRONLY);
	argv[argc - 1] = NULL;
	ft_pipex(fd, &argv[2]);
	close(fd[0]);
	close(fd[1]);
}
