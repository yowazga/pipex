/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_childes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:29:10 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/27 12:48:13 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_pip(t_pip *pip, int i)
{
	if (pip->is_heardoc)
		pip->fd_in = pip->fd_headoc;
	else
		pip->fd_in = open(pip->av[1], O_RDONLY, 0644);
	if (pip->fd_in == -1)
		prit_error(NULL, NULL, 1, pip->av[1]);
	close(pip->pip[READ_END]);
	dup2(pip->fd_in, STDIN_FILENO);
	close(pip->fd_in);
	dup2(pip->pip[WRITE_END], STDOUT_FILENO);
	close(pip->pip[WRITE_END]);
	check_cmd(pip, i + pip->i_cmd);
	if (pip->cmd && pip->path)
		execve(pip->path, pip->cmd, pip->env);
	prit_error(pip->cmd, pip->path, 126, NULL);
}

void	center_pip(t_pip *pip, int i)
{
	dup2(pip->prev, STDIN_FILENO);
	close(pip->prev);
	close(pip->pip[READ_END]);
	dup2(pip->pip[WRITE_END], STDOUT_FILENO);
	close(pip->pip[WRITE_END]);
	check_cmd(pip, i + pip->i_cmd);
	if (pip->cmd && pip->path)
		execve(pip->path, pip->cmd, pip->env);
	prit_error(pip->cmd, pip->path, 126, NULL);
}

void	last_pip(t_pip *pip, int i)
{
	if (pip->is_heardoc)
		pip->fd_out = open(pip->av[pip->num_pipes + 4],
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		pip->fd_out = open(pip->av[pip->num_pipes + 3],
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pip->fd_out == -1)
	{
		if (pip->is_heardoc)
			prit_error(NULL, NULL, 1, pip->av[pip->num_pipes + 4]);
		else
			prit_error(NULL, NULL, 1, pip->av[pip->num_pipes + 3]);
	}
	dup2(pip->fd_out, STDOUT_FILENO);
	close(pip->fd_out);
	dup2(pip->prev, STDIN_FILENO);
	close(pip->prev);
	check_cmd(pip, i + pip->i_cmd);
	if (pip->cmd && pip->path)
		execve(pip->path, pip->cmd, pip->env);
	prit_error(pip->cmd, pip->path, 126, NULL);
}

void	close_prev(t_pip *pip, int i)
{
	if (i != pip->num_pipes)
	{
		if (i != 0)
			close(pip->prev);
		pip->prev = pip->pip[READ_END];
		close(pip->pip[WRITE_END]);
	}
}

void	action_childs(t_pip *pip, int i)
{
	if (i == 0)
		first_pip(pip, i);
	else if (i == pip->num_pipes)
		last_pip(pip, i);
	else
		center_pip(pip, i);
}
