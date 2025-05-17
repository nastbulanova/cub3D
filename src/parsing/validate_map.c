/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 22:06:44 by suroh             #+#    #+#             */
/*   Updated: 2025/05/17 22:11:01 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"
#include "../../inc/structs.h"

static int	count_player_starts(t_map *map)
{
	int		y;
	int		x;
	int		count;
	char	c;

	y = 0;
	count = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			c = map->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	check_cell_enclosed(t_map *map, int y, int x)
{
	if (y == 0 || y == map->rows - 1
		|| x == 0 || x == map->cols - 1)
		exit_error("Map not enclosed by walls");
	if (map->map[y - 1][x] == ' ' || map->map[y + 1][x] == ' '
		|| map->map[y][x - 1] == ' ' || map->map[y][x + 1] == ' ')
		exit_error("Map not enclosed by walls");
}

static void	check_map_enclosure(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			c = map->map[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				check_cell_enclosed(map, y, x);
			x++;
		}
		y++;
	}
}

void	validate_map(t_map *map)
{
	if (count_player_starts(map) != 1)
		exit_error("There must be exactly one player start");
	check_map_enclosure(map);
}
