/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:09:55 by suroh             #+#    #+#             */
/*   Updated: 2025/05/17 19:10:36 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

unsigned int	get_tex_pixel(t_texture *tex, int x, int y)
{
	char	*dst;

	dst = tex->pixels + (y * tex->line_length + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

void	calculate_projection(double perp_dist,
			int *line_height, int *draw_start, int *draw_end)
{
	double	line_h_dbl;
	int		local_line_height;

	line_h_dbl = (double)WINDOW_HEIGHT / perp_dist;
	local_line_height = (int)line_h_dbl;
	*line_height = local_line_height;
	*draw_start = -local_line_height / 2 + WINDOW_HEIGHT / 2;
	if (*draw_start < 0)
	{
		//tex_pos += (double)(-draw_start) * step;/////
		*draw_start = 0;
	}
	*draw_end = local_line_height / 2 + WINDOW_HEIGHT / 2;
	if (*draw_end >= WINDOW_HEIGHT)
		*draw_end = WINDOW_HEIGHT - 1;
}

t_texture	*choose_texture(t_scene *scene, t_ray *ray)
{
	t_texture	*tex;

	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0.0)
			tex = scene->texs->west;
		else
			tex = scene->texs->east;
	}
	else
	{
		if (ray->ray_dir_y > 0.0)
			tex = scene->texs->north;
		else
			tex = scene->texs->south;
	}
	return (tex);
}

int	calculate_tex_x(t_scene *scene, double perp_dist, t_ray *ray,
						t_texture *tex)
{
	int		tex_x;
	double	wall_x;

	if (ray->side == 0)
		wall_x = scene->player->pos_y + perp_dist * ray->ray_dir_y;
	else
		wall_x = scene->player->pos_x + perp_dist * ray->ray_dir_x;
	wall_x = wall_x - floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0.0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0.0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
