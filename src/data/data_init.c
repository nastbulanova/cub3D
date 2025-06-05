/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:56:07 by suroh             #+#    #+#             */
/*   Updated: 2025/06/05 15:24:59 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"
#include "../../libs/libft/libft.h"

static t_cub_data	*allocate_data(void)
{
	t_cub_data	*data;

	data = (t_cub_data *)ft_calloc(1, sizeof(t_cub_data));
	if (!data)
		return (NULL);
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
	if (!map->floor || !map->ceil)
		return (0);
	data->floor = parse_color_string(map->floor);
	data->ceil = parse_color_string(map->ceil);
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
	if (!data
		|| !init_player_and_map(data, map)
		|| !init_textures_and_colors(data, map)
		|| !init_rendering(data, map))
	{
		cleanup_partial_data(data);
		exit_error(map, "Missing floor or ceiling color");
		return (NULL);
	}
	return (data);
}
