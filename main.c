/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:26:06 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/24 11:38:54 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_heardoc(t_pip *pip, char *lim)
{
	while (1)
	{
		write(2, "heredoc> ", 9);
		pip->hrc.read = get_next_line(0);
		if (!pip->hrc.read || ft_strnstr_1(pip->hrc.read, lim, ft_strlen(lim)))
		{
			free(pip->hrc.read);
			break ;
		}
		pip->hrc.stor = ft_strjoin(pip->hrc.stor, pip->hrc.read);
		free(pip->hrc.read);
	}
	if (pipe(pip->hrc.fd) == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	pip->fd_headoc = pip->hrc.fd[0];
	if (!pip->hrc.stor)
	{
		close(pip->hrc.fd[1]);
		return ;
	}
	write(pip->hrc.fd[1], pip->hrc.stor, ft_strlen(pip->hrc.stor));
	close(pip->hrc.fd[1]);
}

void	start_pipe(t_pip *pip)
{
	int	i;

	i = -1;
	pip->pids = malloc(sizeof(pid_t) * pip->num_pipes + 1);
	if (!pip->pids)
		exit(EXIT_FAILURE);
	while (++i <= pip->num_pipes)
	{
		if (i != pip->num_pipes && pipe(pip->pip) == -1)
		{
			perror("pipex");
			exit(EXIT_FAILURE);
		}
		pip->pids[i] = fork();
		if (pip->pids[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pip->pids[i] == 0)
			action_childs(pip, i);
		close_prev(pip, i);
	}
	close(pip->prev);
}

void	start_arguments(t_pip *pip)
{
	if (!ft_strncmp(pip->av[1], "here_doc", ft_strlen(pip->av[1])))
	{
		init_heardoc(pip, pip->av[2]);
		pip->num_pipes = pip->ac - 5;
		pip->is_heardoc = 1;
		pip->i_cmd = 3;
	}
	else
	{
		pip->num_pipes = pip->ac - 4;
		pip->is_heardoc = 0;
		pip->i_cmd = 2;
	}
}

int	wait_for_childs(t_pip *pip)
{
	int	i;
	int	status;

	i = 0;
	while (i <= pip->num_pipes)
	{
		if (waitpid(pip->pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	free(pip->pids);
	return (status >> 8);
}

int	main(int ac, char *av[], char *env[])
{
	t_pip	pip;

	if (ac > 4)
	{
		pip.av = av;
		pip.env = env;
		pip.ac = ac;
		start_arguments(&pip);
		start_pipe(&pip);
		return (wait_for_childs(&pip));
	}
	else
		return (EXIT_FAILURE);
}
