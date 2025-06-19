/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:15:55 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/24 15:47:35 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	cont_word(char *cmd)
{
	t_variabls	v;

	v.i = 0;
	v.k = 0;
	while (cmd[v.i])
	{
		while (cmd[v.i] <= 32 && cmd[v.i])
			v.i++;
		if (cmd[v.i] == 39 || cmd[v.i] == 34)
		{
			v.c = cmd[v.i++];
			while (cmd[v.i] && cmd[v.i] != v.c)
				v.i++;
			v.i++;
			v.k++;
		}
		else if (cmd[v.i])
		{
			while (cmd[v.i] && cmd[v.i] != ' ' && cmd[v.i] != '\t')
				v.i++;
			v.k++;
		}
	}
	return (v.k);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;

	i = 0;
	if (to_find[i] == '\0')
		return (str);
	while (str[i])
	{
		while (str[i] == to_find[i])
		{
			i++;
			if (to_find[i] == '\0')
				return (str);
		}
		str++;
		i = 0;
	}
	return (0);
}

char	*ft_strnstr_1(char *str, char *to_find, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i] == '\n' && to_find[i] == '\0')
		return (str);
	while (str[i] && j + i < len)
	{
		while (str[i] == to_find[i] && j + i < len)
		{
			i++;
			if (to_find[i] == '\0')
			{
				if (ft_strlen(str) - 1 == ft_strlen(to_find))
					return (str);
			}
		}
		str++;
		i = 0;
		j++;
	}
	return (0);
}

void	check_cmd(t_pip *pip, int cmd)
{
	if (ft_strchr(pip->av[cmd], 39) || ft_strchr(pip->av[cmd], 34))
	{
		pip->cmd = second_split(pip->av[cmd]);
		if (pip->cmd[0] == NULL)
			ft_printf("pipex: %s: command not found\n", pip->av[cmd]);
		pip->path = get_path(pip, pip->cmd[0], 0);
	}
	else if (pip->av[cmd][0] == '/' || pip->av[cmd][0] == '.'
		|| (ft_strstr(pip->av[cmd], ".sh") && ft_strchr(pip->av[cmd], 47)))
	{
		pip->cmd = ft_split(pip->av[cmd], ' ');
		if (pip->cmd[0] == NULL)
			ft_printf("pipex: %s: command not found\n", pip->av[cmd]);
		if (pip->cmd[0][0] == '/' || pip->cmd[0][0] == '.')
			pip->path = get_path(pip, pip->cmd[0], 1);
		else
			pip->path = get_path(pip, pip->cmd[0], 0);
	}
	else
	{
		pip->cmd = ft_split(pip->av[cmd], ' ');
		if (pip->cmd[0] == NULL)
			ft_printf("pipex: %s: command not found\n", pip->av[cmd]);
		pip->path = get_path(pip, pip->cmd[0], 0);
	}
}

void	prit_error(char **cmd, char *path, int e, char *infile)
{
	int	i;

	i = 0;
	if (path != NULL)
		free(path);
	if (cmd != NULL)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
	}
	if (!infile)
		ft_printf("pipex: %s\n", strerror(errno));
	else
		ft_printf("pipex: %s: %s\n", infile, strerror(errno));
	exit(e);
}
