/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:49:41 by suroh             #+#    #+#             */
/*   Updated: 2025/05/17 18:51:37 by suroh            ###   ########.fr       */
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

void	draw_column(t_scene *scene, t_texture *tex, int draw_start,
					int draw_end, int tex_x, double step, int x)
{
	double			tex_pos;
	int				tex_y;
	unsigned int	color;

	tex_pos = 0.0;
	while (draw_start <= draw_end)
	{
		tex_y = ((int)tex_pos) & (tex->height - 1);
		tex_pos += step;
		color = get_tex_pixel(tex, tex_x, tex_y);
		put_pixel(scene->draw->img, x, draw_start, color);
		draw_start++;
	}
}

void	render_column(t_cub_data *data, t_scene *scene, int x)
{
	t_ray		ray;
	int			map_x;
	int			map_y;
	double		perp_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_texture	*tex;
	int			tex_x;
	double		step;

	calculate_ray(scene, x, &ray);
	init_ray_steps(scene, &ray, &map_x, &map_y);
	perform_dda(data, &ray, &map_x, &map_y);
	perp_dist = calculate_wall_distance(scene, &ray, map_x, map_y);
	calculate_projection(perp_dist, &line_height, &draw_start, &draw_end);
	tex = choose_texture(scene, &ray);
	tex_x = calculate_tex_x(scene, perp_dist, &ray, tex);
	step = 1.0 * tex->height / (double)line_height;
	draw_column(scene, tex, draw_start, draw_end, tex_x, step, x);
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
