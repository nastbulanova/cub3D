/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:12:43 by suroh             #+#    #+#             */
/*   Updated: 2025/06/04 11:51:26 by suroh            ###   ########.fr       */
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

static void	free_single_texture(void *mlx, t_texture *tex)
{
	if (!tex)
	{
		printf("free_single_texture: tex == NULL\n");
		return ;
	}
	if (mlx && tex->img_ptr)
	{
		printf("free_single_texture: destroying one texture\n");
		mlx_destroy_image(mlx, tex->img_ptr);
	}
	free(tex);
}

void	free_textures(void *mlx, t_textures *textures)
{
	if (!textures)
	{
		printf("free_textures: textures == NULL\n");
		return ;
	}
	free_single_texture(mlx, textures->north);
	free_single_texture(mlx, textures->south);
	free_single_texture(mlx, textures->east);
	free_single_texture(mlx, textures->west);
	free(textures);
}

void	free_drawing_resources(void *mlx, t_draw *draw)
{
	if (!draw)
	{
		printf("free_drawing_resources: draw == NULL\n");
		return ;
	}
	if (draw->img)
	{
		printf("free_drawing_resources: destroying off-screen image\n");
		if (mlx && draw->img && draw->img->img_ptr)
			mlx_destroy_image(mlx, draw->img->img_ptr);
		free(draw->img);
	}
	free(draw);
}

void	free_scene(void *mlx, t_scene *scene)
{
	if (!scene)
	{
		printf("free_scene: scene == NULL\n");
		return ;
	}
	printf("free_scene: freeing map\n");
	free_map_data(scene->map);
	printf("free_scene: freeing textures\n");
	free_textures(mlx, scene->texs);
	printf("free_scene: freeing drawing resources\n");
	free_drawing_resources(mlx, scene->draw);
	printf("free_scene: freeing player and scene\n");
	free(scene->player);
	free(scene);
}
