/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:03:09 by suroh             #+#    #+#             */
/*   Updated: 2025/05/17 20:57:28 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_after_line(char *line)
{
	char	*after_line;
	char	*temp;
	int		len;

	after_line = ft_strchr(line, '\n');
	if (!after_line)
	{
		free(line);
		return (NULL);
	}
	len = ft_strlen(after_line);
	temp = (char *)malloc(len);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, after_line + 1, len);
	if (temp[0] == '\0')
	{
		free(line);
		free(temp);
		return (NULL);
	}
	free(line);
	return (temp);
}

static char	*print_current_line(char *line)
{
	int		i;
	char	*print_line;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i++] == '\n')
			break ;
	}
	print_line = (char *)malloc(i + 1);
	ft_strlcpy(print_line, line, i + 1);
	return (print_line);
}

static char	*get_current_line(char *line, int fd)
{
	ssize_t	read_check;
	char	*buff;
	char	*temp;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!line || !ft_strchr(line, '\n'))
	{
		read_check = read(fd, buff, BUFFER_SIZE);
		if (read_check <= 0)
			break ;
		buff[read_check] = '\0';
		if (!line)
			line = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(line, buff);
			free(line);
			line = temp;
		}
	}
	free(buff);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_current_line(line, fd);
	if (!line)
		return (NULL);
	next_line = print_current_line(line);
	line = get_after_line(line);
	return (next_line);
}
