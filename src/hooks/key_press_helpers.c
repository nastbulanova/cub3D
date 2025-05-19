/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:02:28 by suroh             #+#    #+#             */
/*   Updated: 2025/05/19 22:03:04 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

void	handle_movement_keys(int keycode, t_cub_data *data, double move_speed)
{
	if (keycode == KEY_W)
		move_forward_backward(data, data->scene->player, move_speed);
	else if (keycode == KEY_S)
		move_forward_backward(data, data->scene->player, -move_speed);
	else if (keycode == KEY_A)
		move_left_right(data, data->scene->player, -move_speed);
	else if (keycode == KEY_D)
		move_left_right(data, data->scene->player, move_speed);
}

void	handle_rotation_keys(int keycode, t_cub_data *data, double rot_speed)
{
	if (keycode == KEY_LEFT)
		rotate_player(data->scene->player, rot_speed);
	else if (keycode == KEY_RIGHT)
		rotate_player(data->scene->player, -rot_speed);
}

void	update_display(t_cub_data *data)
{
	if (data->scene && data->scene->draw && data->scene->draw->mlx_connection
		&& data->scene->draw->mlx_window && data->scene->draw->img
		&& data->scene->draw->img->img_ptr)
	{
		render_scene(data, data->scene);
		mlx_put_image_to_window(data->scene->draw->mlx_connection,
			data->scene->draw->mlx_window, data->scene->draw->img->img_ptr,
			0, 0);
	}
}
