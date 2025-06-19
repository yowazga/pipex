/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:42:08 by yowazga           #+#    #+#             */
/*   Updated: 2023/02/04 16:13:00 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	cont_char(char *cmd, int *st, char check)
{
	int	i;

	i = 0;
	while (cmd[*st] && cmd[*st] != check)
	{
		(*st)++;
		i++;
	}
	return (i);
}

void	copy_colom(char **cmds, char *cmd, t_variabls *v)
{
	v->j = 0;
	v->c = cmd[v->k++];
	while (cmd[v->k] && cmd[v->k] != v->c)
	{
		cmds[v->i][v->j] = cmd[v->k];
		v->j++;
		v->k++;
	}
	v->k++;
	cmds[v->i][v->j] = 0;
}

void	copy_table(char **cmds, char *cmd, int cw)
{
	t_variabls	v;

	v.i = -1;
	v.k = 0;
	while (++v.i < cw)
	{
		while (cmd[v.k] && cmd[v.k] <= 32)
			v.k++;
		if (cmd[v.k] == 39 || cmd[v.k] == 34)
			copy_colom(cmds, cmd, &v);
		else if (cmd[v.k])
		{
			v.j = 0;
			while (cmd[v.k] && cmd[v.k] != ' ')
			{
				cmds[v.i][v.j] = cmd[v.k];
				v.j++;
				v.k++;
			}
			cmds[v.i][v.j] = 0;
		}
	}
	cmds[v.i] = NULL;
}

void	alloc_table(char **cmds, char *cmd, int j, int cw)
{
	int		i;
	char	check;

	i = 0;
	while (i < cw)
	{
		while (cmd[j] && cmd[j] <= 32)
			j++;
		if (cmd[j] == 34 || cmd[j] == 39)
		{
			check = cmd[j++];
			cmds[i++] = malloc (cont_char(cmd, &j, check) + 1);
			if (!cmds[i - 1])
				return ;
			j++;
		}
		else if (cmd[j])
		{
			cmds[i++] = malloc(cont_char(cmd, &j, ' ') + 1);
			if (!cmds[i - 1])
				return ;
		}
	}
}

char	**second_split(char *cmd)
{
	char	**cmds;
	int		i;
	int		j;
	int		cw;

	i = 0;
	j = 0;
	cw = cont_word(cmd);
	cmds = malloc(sizeof(char *) * (cw + 1));
	if (!cmds)
		return (0);
	alloc_table(cmds, cmd, i, cw);
	copy_table(cmds, cmd, cw);
	return (cmds);
}
