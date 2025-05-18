/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:05:56 by suroh             #+#    #+#             */
/*   Updated: 2025/05/18 19:38:10 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

void	set_dimensions(t_map *map, int *width, int *height)
{
	*width = WINDOW_WIDTH;
	*height = WINDOW_HEIGHT;
	if (map && map->res_w > 0)
		*width = map->res_w;
	if (map && map->res_h > 0)
		*height = map->res_h;
}

int	init_image(t_draw *draw, int width, int height)
{
	draw->img = NULL;
	draw->img = (t_img *)malloc(sizeof(t_img));
	if (!draw->img)
		return (0);
	draw->img->img_ptr = mlx_new_image(draw->mlx_connection, width, height);
	draw->img->pixels = mlx_get_data_addr(draw->img->img_ptr, &draw->img->bpp,
			&draw->img->line_length, &draw->img->endian);
	return (1);
}

t_scene	*init_scene_basics(t_cub_data *data, t_map *map)
{
	t_scene	*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->draw = NULL;
	scene->texs = NULL;
	scene->player = data->player;
	scene->map = map;
	scene->cols = data->cols;
	scene->rows = data->rows;
	scene->fov_scale = get_fov_scale();
	scene->floor = rgb_to_color(&(data->floor));
	scene->ceil = rgb_to_color(&(data->ceil));
	return (scene);
}

int	setup_draw_and_textures(t_scene *scene, t_map *map)
{
	scene->draw = draw_init(map);
	if (!scene->draw)
		return (0);
	scene->texs = load_textures(scene->draw, map);
	if (!scene->texs)
	{
		free(scene->draw->img);
		free(scene->draw);
		return (0);
	}
	return (1);
}
