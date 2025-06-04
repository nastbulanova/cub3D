/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:03:09 by suroh             #+#    #+#             */
/*   Updated: 2025/06/04 14:46:17 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*g_line = NULL;

static char	*get_after_line(char *g_line)
{
	char	*after_line;
	char	*temp;
	int		len;

	after_line = ft_strchr(g_line, '\n');
	if (!after_line)
	{
		free(g_line);
		return (NULL);
	}
	len = ft_strlen(after_line);
	temp = (char *)malloc(len);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, after_line + 1, len);
	if (temp[0] == '\0')
	{
		free(g_line);
		free(temp);
		return (NULL);
	}
	free(g_line);
	return (temp);
}

static char	*print_current_line(char *g_line)
{
	int		i;
	char	*print_line;

	i = 0;
	while (g_line[i] != '\0')
	{
		if (g_line[i++] == '\n')
			break ;
	}
	print_line = (char *)malloc(i + 1);
	if (!print_line)
		return (NULL);
	ft_strlcpy(print_line, g_line, i + 1);
	return (print_line);
}

static char	*get_current_line(char *g_line, int fd)
{
	ssize_t	read_check;
	char	*buff;
	char	*temp;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!g_line || !ft_strchr(g_line, '\n'))
	{
		read_check = read(fd, buff, BUFFER_SIZE);
		if (read_check <= 0)
			break ;
		buff[read_check] = '\0';
		if (!g_line)
			g_line = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(g_line, buff);
			free(g_line);
			g_line = temp;
		}
	}
	free(buff);
	return (g_line);
}

void	g_nl_cleanup(void)
{
	if (g_line)
	{
		free(g_line);
		g_line = NULL;
	}
}

char	*get_next_line(int fd)
{
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	g_line = get_current_line(g_line, fd);
	if (!g_line)
		return (NULL);
	next_line = print_current_line(g_line);
	g_line = get_after_line(g_line);
	return (next_line);
}
