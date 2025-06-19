/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:37:39 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/24 08:24:19 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/**************************************************************/
/*                        INCLUDES                            */
/**************************************************************/

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"

/**************************************************************/
/*                            DEFINES                         */
/**************************************************************/

# define PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"
# define READ_END 0
# define WRITE_END 1

/**************************************************************/
/*                            STRUCT                          */
/**************************************************************/

typedef struct s_vriabls
{
	int		i;
	int		j;
	int		k;
	char	c;
}	t_variabls;

typedef struct s_herdoc
{
	char	*stor;
	char	*read;
	int		fd[2];
}	t_herdoc;

typedef struct s_pip
{
	int			pip[2];
	int			prev;
	pid_t		*pids;
	int			fd_in;
	int			fd_out;
	int			num_pipes;
	int			fd_headoc;
	int			is_heardoc;
	int			i_cmd;
	char		**env;
	char		**av;
	int			ac;
	char		**cmd;
	char		*path;
	t_herdoc	hrc;
}	t_pip;

/**************************************************************/
/*                      FUNCTION PIPEX                        */
/**************************************************************/

char	*ft_strstr(char *str, char *to_find);
char	*ft_strnstr_1(char *str, char *to_find, int len);
char	**second_split(char *cmd);
char	*get_path(t_pip *pip, char *cmd0, int status);
int		cont_word(char *cmd);
void	check_cmd(t_pip *pip, int cmd);
void	prit_error(char **cmd, char *path, int e, char *infile);
void	action_childs(t_pip *pip, int i);
void	first_pip(t_pip *pip, int i);
void	center_pip(t_pip *pip, int i);
void	last_pip(t_pip *pip, int i);
void	close_prev(t_pip *pip, int i);

#endif