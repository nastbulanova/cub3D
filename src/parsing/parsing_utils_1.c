/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:11:42 by suroh             #+#    #+#             */
/*   Updated: 2025/05/17 22:53:36 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"
#include "../../inc/structs.h"
#include "../../libs/get_next_line/get_next_line.h"
#include "../../libs/libft/libft.h"

void	parse_texture_line(t_map *map, char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
		exit_error("Invalid texture line");
	if (ft_strcmp(tokens[0], "NO") == 0)
		map->file_no = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "SO") == 0)
		map->file_so = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "WE") == 0)
		map->file_we = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "EA") == 0)
		map->file_ea = ft_strdup(tokens[1]);
	else
		exit_error("Unknown texture identifier");
	ft_free_split(tokens);
}

void	parse_color_line(char **target, char *line)
{
	int	i;

	i = 1;
	while (line[i] == ' ')
		i++;
	*target = ft_strdup(line + i);
	if (!*target)
		exit_error("malloc failed");
}

void	add_map_line(char *line, char ***grid, int *rows)
{
	char	**tmp;

	tmp = realloc_list(*grid, *rows + 1);
	if (!tmp)
		exit_error("Memory error");
	*grid = tmp;
	(*grid)[*rows] = ft_strdup(line);
	(*rows)++;
}

void	process_line(t_map *map, char *line, char ***grid, int *rows)
{
	if (is_texture_line(line))
		parse_texture_line(map, line);
	else if (line[0] == 'F')
		parse_color_line(&map->floor, line);
	else if (line[0] == 'C')
		parse_color_line(&map->ceil, line);
	else if (is_map_line(line))
		add_map_line(line, grid, rows);
}

void	read_map_lines(int fd, t_map *map, char ***grid, int *rows)
{
	char	*line;

	while ((line = get_next_line(fd)))
	{
		process_line(map, line, grid, rows);
		free(line);
	}
}
