/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:11:42 by suroh             #+#    #+#             */
/*   Updated: 2025/06/04 20:03:30 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"
#include "../../inc/structs.h"
#include "../../libs/get_next_line/get_next_line.h"
#include "../../libs/libft/libft.h"

void	parse_color_line(char **target, char *line)
{
	int		i;
	t_map	*map;

	(void)map;
	i = 1;
	while (line[i] == ' ')
		i++;
	*target = ft_strdup(line + i);
	if (!*target)
		exit_error(NULL, "malloc failed");
}

void	add_map_line(t_map *map, char *line, char ***grid, int *rows)
{
	char	**tmp;

	(void)*map;
	tmp = realloc_list(*grid, *rows + 1);
	if (!tmp)
		exit_error(NULL, "Memory error");
	*grid = tmp;
	(*grid)[*rows] = ft_strdup(line);
	(*rows)++;
}

void	process_line(t_map *map, char *line, char ***grid, int *rows)
{
	if (is_blank_line(line))
		return ;
	if (line[0] == 'R')
		parse_resolution_line(map, line);
	else if (is_texture_line(line))
		parse_texture_line(map, line);
	else if (line[0] == 'F')
		parse_color_line(&map->floor, line);
	else if (line[0] == 'C')
		parse_color_line(&map->ceil, line);
	else if (is_map_line(line))
		add_map_line(map, line, grid, rows);
	else
	{
		printf("Invalid line: '%s'\n", line);
		free(line);
		exit_error(map, NULL);
	}
}

void	read_map_lines(int fd, t_map *map)
{
	char	*line;
	char	*stripped_line;
	char	**grid;
	int		rows;

	grid = NULL;
	rows = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		stripped_line = strip_line(line);
		free(line);
		if (!is_blank_line(stripped_line))
			process_line(map, stripped_line, &grid, &rows);
		free(stripped_line);
	}
	map->map = grid;
	map->rows = rows;
}
