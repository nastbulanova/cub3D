/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:49:41 by suroh             #+#    #+#             */
/*   Updated: 2025/05/27 14:58:36 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = img->pixels + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_ceil_floor(t_scene *scene)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < WINDOW_HEIGHT / 2)
			color = scene->floor;
		else
			color = scene->ceil;
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel(scene->draw->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_column(t_scene *scene, t_texture *tex, t_ray *ray)
{
	double			tex_pos;
	int				tex_y;
	unsigned int	color;

	tex_pos = ray->tex_pos;
	while (ray->draw_start <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_pos += ray->tex_step;
		color = get_tex_pixel(tex, ray->tex_x, tex_y);
		put_pixel(scene->draw->img, ray->screen_x, ray->draw_start, color);
		ray->draw_start++;
	}
}

void	render_column(t_cub_data *data, t_scene *scene, int x)
{
	t_ray			ray;
	t_map_pos		map_pos;
	t_projection	proj;
	t_texture		*tex;

	ray.screen_x = x;
	calculate_ray(scene, x, &ray);
	init_ray_steps(scene, &ray, &map_pos.x, &map_pos.y);
	perform_dda(data, &ray, &map_pos.x, &map_pos.y);
	proj.perp_dist = calculate_wall_distance(scene, &ray, map_pos.x, map_pos.y);
	proj.line_height = (int)(WINDOW_HEIGHT / proj.perp_dist);
	ray.draw_start = -proj.line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray.draw_start < 0)
		ray.draw_start = 0;
	ray.draw_end = proj.line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray.draw_end >= WINDOW_HEIGHT)
		ray.draw_end = WINDOW_HEIGHT - 1;
	tex = choose_texture(scene, &ray);
	ray.tex_x = calculate_tex_x(scene, proj.perp_dist, &ray, tex);
	ray.tex_step = 1.0 * tex->height / (double)proj.line_height;
	int true_draw_start = -proj.line_height / 2 + WINDOW_HEIGHT / 2;
	int clipped_draw_start = ray.draw_start;
	ray.tex_pos = (clipped_draw_start - true_draw_start) * ray.tex_step;
	draw_column(scene, tex, &ray);
}

void	render_scene(t_cub_data *data, t_scene *scene)
{
	int		x;

	scene->player = data->player;
	draw_ceil_floor(scene);
	scene->plane_x = -(scene->player->d_y) * scene->fov_scale;
	scene->plane_y = (scene->player->d_x) * scene->fov_scale;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		render_column(data, scene, x);
		x++;
	}
}
