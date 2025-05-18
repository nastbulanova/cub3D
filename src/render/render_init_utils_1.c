/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:05:56 by suroh             #+#    #+#             */
/*   Updated: 2025/05/18 19:36:45 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

float	get_fov_scale(void)
{
	float	fov_rad;

	fov_rad = (float)FOV * PI_CONST / 180.0;
	return (tanf(fov_rad / 2.0f));
}

int	rgb_to_color(t_rgb *color)
{
	return ((color->red << 16) | (color->green << 8) | (color->blue));
}
