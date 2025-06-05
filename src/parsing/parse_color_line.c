/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:20:08 by suroh             #+#    #+#             */
/*   Updated: 2025/06/05 20:25:19 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"
#include "../../inc/structs.h"
#include "../../libs/get_next_line/get_next_line.h"
#include "../../libs/libft/libft.h"

static char	**get_color_parts(char *colors, char *line, t_map *map)
{
	char	**parts;

	parts = ft_split(colors, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3] != NULL)
	{
		ft_free_split(parts);
		free(line);
		close(map->fd_cub);
		exit_error(map, "Invalid color format");
	}
	return (parts);
}

static int	is_num(const char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static char	*check_color_value_and_dup(char *colors, char **parts, char *line,
			t_map *map)
{
	int		r;
	int		g;
	int		b;
	char	*dup;

	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_free_split(parts);
		free(line);
		exit_error(map, "Invalid color value");
	}
	dup = ft_strdup(colors);
	if (!dup)
	{
		ft_free_split(parts);
		free(line);
		exit_error(map, "malloc failed");
	}
	ft_free_split(parts);
	return (dup);
}

void	parse_color_line(t_map *map, char **target, char *line)
{
	int		i;
	char	*colors;
	char	**parts;
	char	*dup;

	i = 1;
	while (line[i] == ' ')
		i++;
	colors = line + i;
	parts = get_color_parts(colors, line, map);
	if (!is_num(parts[0]) || !is_num(parts[1]) || !is_num(parts[2]))
	{
		ft_free_split(parts);
		free(line);
		close(map->fd_cub);
		exit_error(map, "Invalid character in color");
	}
	dup = check_color_value_and_dup(colors, parts, line, map);
	*target = dup;
}
