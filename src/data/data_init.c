/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:56:07 by suroh             #+#    #+#             */
/*   Updated: 2025/05/18 19:44:43 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

static t_cub_data	*allocate_data(void)
{
	t_cub_data	*data;

	data = (t_cub_data *)malloc(sizeof(t_cub_data));
	if (!data)
		return (NULL);
	data->player = NULL;
	data->scene = NULL;
	return (data);
}

static int	init_player_and_map(t_cub_data *data, t_map *map)
{
	data->player = player_init(map);
	if (!data->player)
		return (0);
	data->map = map->map;
	data->cols = map->cols;
	data->rows = map->rows;
	return (1);
}

static int	init_textures_and_colors(t_cub_data *data, t_map *map)
{
	t_rgb	floor_color;
	t_rgb	ceil_color;

	if (!map->floor || !map->ceil)
		return (0);
	floor_color = parse_color_string(map->floor);
	data->floor.red = floor_color.red;
	data->floor.green = floor_color.green;
	data->floor.blue = floor_color.blue;
	ceil_color = parse_color_string(map->ceil);
	data->ceil.red = ceil_color.red;
	data->ceil.green = ceil_color.green;
	data->ceil.blue = ceil_color.blue;
	return (1);
}

static int	init_rendering(t_cub_data *data, t_map *map)
{
	data->scene = render_init(data, map);
	return (data->scene != NULL);
}

t_cub_data	*data_init(t_map *map)
{
	t_cub_data	*data;

	data = allocate_data();
	if (!data)
		return (NULL);
	if (!init_player_and_map(data, map))
	{
		cleanup_partial_data(data);
		return (NULL);
	}
	if (!init_textures_and_colors(data, map))
	{
		cleanup_partial_data(data);
		exit_error("Missing floor or ceiling color");
	}
	if (!init_rendering(data, map))
	{
		cleanup_partial_data(data);
		return (NULL);
	}
	return (data);
}
