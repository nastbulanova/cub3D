/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:42:32 by suroh             #+#    #+#             */
/*   Updated: 2025/05/18 18:55:16 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

char	find_player_position(t_map *map, int *x_pos, int *y_pos)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'E' || map->map[y][x] == 'W')
			{
				*x_pos = x;
				*y_pos = y;
				return (map->map[y][x]);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static void	set_player_north_south(t_player *player, char direction)
{
	player->d_x = 0;
	if (direction == 'N')
	{
		player->d_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else
	{
		player->d_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}

static void	set_player_east_west(t_player *player, char direction)
{
	player->d_y = 0;
	if (direction == 'E')
	{
		player->d_x = 1;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else
	{
		player->d_x = -1;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

void	set_player_directions(t_player *player, char direction)
{
	if (direction == 'N' || direction == 'S')
		set_player_north_south(player, direction);
	else
		set_player_east_west(player, direction);
}

t_player	*player_init(t_map *map)
{
	t_player	*player;
	int			x_pos;
	int			y_pos;
	char		direction;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	direction = find_player_position(map, &x_pos, &y_pos);
	if (!direction)
	{
		free(player);
		return (NULL);
	}
	player->pos_x = x_pos + 0.5;
	player->pos_y = y_pos + 0.5;
	set_player_directions(player, direction);
	map->map[y_pos][x_pos] = '0';
	return (player);
}
