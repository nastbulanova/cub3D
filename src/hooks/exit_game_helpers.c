/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:12:43 by suroh             #+#    #+#             */
/*   Updated: 2025/05/19 22:18:40 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

void	free_map_data(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->map)
	{
		i = 0;
		while (i < map->rows && map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
	free(map->file_no);
	free(map->file_so);
	free(map->file_we);
	free(map->file_ea);
	free(map->floor);
	free(map->ceil);
	free(map);
}

void	free_textures(void *mlx, t_textures *textures)
{
	if (!textures)
		return ;
	if (mlx && textures->north && textures->north->img_ptr)
		mlx_destroy_image(mlx, textures->north->img_ptr);
	if (mlx && textures->south && textures->south->img_ptr)
		mlx_destroy_image(mlx, textures->south->img_ptr);
	if (mlx && textures->east && textures->east->img_ptr)
		mlx_destroy_image(mlx, textures->east->img_ptr);
	if (mlx && textures->west && textures->west->img_ptr)
		mlx_destroy_image(mlx, textures->west->img_ptr);
	free(textures->north);
	free(textures->south);
	free(textures->east);
	free(textures->west);
	free(textures);
}

void	free_drawing_resources(void *mlx, t_draw *draw)
{
	if (!draw)
		return ;
	if (mlx && draw->img && draw->img->img_ptr)
		mlx_destroy_image(mlx, draw->img->img_ptr);
	free(draw->img);
	free(draw);
}

void	free_scene(void *mlx, t_scene *scene)
{
	if (!scene)
		return ;
	free_map_data(scene->map);
	free_textures(mlx, scene->texs);
	free_drawing_resources(mlx, scene->draw);
	free(scene->player);
	free(scene);
}
