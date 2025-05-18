/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:55:27 by suroh             #+#    #+#             */
/*   Updated: 2025/05/18 19:35:13 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

t_texture	*add_wall_pixels(t_draw *draw, char *file)
{
	t_texture	*temp_tex;

	temp_tex = NULL;
	temp_tex = (t_texture *)malloc(sizeof(t_texture));
	if (!temp_tex)
		return (NULL);
	temp_tex->img_ptr = mlx_xpm_file_to_image(draw->mlx_connection, file,
			&temp_tex->width, &temp_tex->height);
	if (!temp_tex->img_ptr)
		return (free(temp_tex), NULL);
	temp_tex->pixels = mlx_get_data_addr(temp_tex->img_ptr,
			&temp_tex->bpp, &temp_tex->line_length, &temp_tex->endian);
	return (temp_tex);
}

t_textures	*load_textures(t_draw *draw, t_map *map)
{
	t_textures	*texs;

	texs = (t_textures *)malloc(sizeof(t_textures));
	if (!texs)
		return (NULL);
	texs->north = NULL;
	texs->south = NULL;
	texs->east = NULL;
	texs->west = NULL;
	texs->north = add_wall_pixels(draw, map->file_no);
	if (!texs->north)
		return (free(texs), NULL);
	texs->south = add_wall_pixels(draw, map->file_so);
	if (!texs->south)
		return (free_textures(texs), NULL);
	texs->east = add_wall_pixels(draw, map->file_ea);
	if (!texs->east)
		return (free_textures(texs), NULL);
	texs->west = add_wall_pixels(draw, map->file_we);
	if (!texs->west)
		return (free_textures(texs), NULL);
	return (texs);
}

t_draw	*draw_init(t_map *map)
{
	t_draw	*draw;
	int		width;
	int		height;

	set_dimensions(map, &width, &height);
	draw = NULL;
	draw = (t_draw *)malloc(sizeof(t_draw));
	if (!draw)
		return (NULL);
	draw->mlx_connection = mlx_init();
	draw->mlx_window = mlx_new_window
		(draw->mlx_connection, width, height, "cub3D");
	if (!init_image(draw, width, height))
	{
		free(draw);
		return (NULL);
	}
	return (draw);
}

t_scene	*render_init(t_cub_data *data, t_map *map)
{
	t_scene	*scene;

	scene = init_scene_basics(data, map);
	if (!scene)
		return (NULL);
	if (!setup_draw_and_textures(scene, map))
	{
		free(scene);
		return (NULL);
	}
	return (scene);
}
