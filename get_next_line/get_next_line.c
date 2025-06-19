/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:56:22 by yowazga           #+#    #+#             */
/*   Updated: 2022/12/25 14:55:45 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*buf_with_line(int fd, char *buf_over)
{
	char	*buffer;
	int		nr;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char ));
	if (!buffer)
		return (0);
	nr = 1;
	while ((!ft_strchr_2(buf_over, '\n')) && nr != 0)
	{
		nr = read(fd, buffer, BUFFER_SIZE);
		if (nr == -1)
		{
			free(buffer);
			free(buf_over);
			return (0);
		}
		buffer[nr] = '\0';
		buf_over = ft_strjoin_2(buf_over, buffer);
	}
	free(buffer);
	return (buf_over);
}

char	*cpy_line(char *buf_over)
{
	char	*str;
	int		i;

	i = 0;
	if (!buf_over[i])
		return (0);
	while (buf_over[i] != '\n' && buf_over[i])
		i++;
	if (buf_over[i] == '\n')
		i++;
	str = malloc(i + 1);
	if (!str)
		return (0);
	i = 0;
	while (buf_over[i] != '\n' && buf_over[i])
	{
		str[i] = buf_over[i];
		i++;
	}
	if (buf_over[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*overflow(char *buf_over)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (buf_over[0] == '\0')
	{
		free(buf_over);
		return (0);
	}
	while (buf_over[i] != '\n' && buf_over[i])
		i++;
	if (buf_over[i] == '\n')
		i++;
	str = malloc(ft_strlen_2(buf_over) - i + 1);
	while (buf_over[i])
	{
		str[j] = buf_over[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(buf_over);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buf_over;
	char		*line;

	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (0);
	buf_over = buf_with_line(fd, buf_over);
	if (!buf_over)
		return (0);
	line = cpy_line(buf_over);
	buf_over = overflow(buf_over);
	return (line);
}
