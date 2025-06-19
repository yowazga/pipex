/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:10:22 by yowazga           #+#    #+#             */
/*   Updated: 2022/12/25 14:56:32 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*buf_with_line(int fd, char *buf_over);
char	*cpy_line(char *buf_over);
char	*overflow(char *buf_over);

int		ft_strlen_2(char *str);
char	*ft_strchr_2(char *str, char c);
char	*ft_strjoin_2(char *s1, char *s2);

#endif
