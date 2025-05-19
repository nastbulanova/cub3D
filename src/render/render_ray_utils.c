/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:06:37 by suroh             #+#    #+#             */
/*   Updated: 2025/05/18 23:13:07 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

void	calculate_ray(t_scene *scene, int x, t_ray *ray)
{
	double	local_camera_x;

	local_camera_x = 2.0 * x / (double)WINDOW_WIDTH - 1.0;
	ray->ray_dir_x = scene->player->d_x + scene->plane_x * local_camera_x;
	ray->ray_dir_y = scene->player->d_y + scene->plane_y * local_camera_x;
	if (ray->ray_dir_x == 0.0)
		ray->ray_dir_x = 0.0001;
	if (ray->ray_dir_y == 0.0)
		ray->ray_dir_y = 0.0001;
	ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

static void	init_map_position(t_scene *scene, int *map_x, int *map_y)
{
	*map_x = (int)scene->player->pos_x;
	*map_y = (int)scene->player->pos_y;
}

void	init_ray_steps(t_scene *scene, t_ray *ray, int *map_x, int *map_y)
{
	init_map_position(scene, map_x, map_y);
	if (ray->ray_dir_x < 0.0)
	{
		ray->step_x = -1;
		ray->side_dist_x
			= (scene->player->pos_x - (double)*map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x
			= ((double)*map_x + 1.0 - scene->player->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0.0)
	{
		ray->step_y = -1;
		ray->side_dist_y
			= (scene->player->pos_y - (double)*map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y
			= ((double)*map_y + 1.0 - scene->player->pos_y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_cub_data *data, t_ray *ray, int *map_x, int *map_y)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			*map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			*map_y += ray->step_y;
			ray->side = 1;
		}
		if (*map_x < 0 || *map_x >= data->cols
			|| *map_y < 0 || *map_y >= data->rows)
			break ;
		if (data->map[*map_y][*map_x] == '1')
			hit = 1;
	}
}

double	calculate_wall_distance(t_scene *scene,
			t_ray *ray, int map_x, int map_y)
{
	double	perp_dist;

	if (ray->side == 0)
		perp_dist
			= (map_x - scene->player->pos_x
				+ (1 - ray->step_x) / 2.0) / ray->ray_dir_x;
	else
		perp_dist
			= (map_y - scene->player->pos_y
				+ (1 - ray->step_y) / 2.0) / ray->ray_dir_y;
	return (perp_dist);
}
