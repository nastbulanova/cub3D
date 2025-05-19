/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:40:03 by suroh             #+#    #+#             */
/*   Updated: 2025/05/18 22:45:09 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

static int	exit_game(t_cub_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

static int	validate_data(t_cub_data *data)
{
	if (!data)
	{
		printf("ERROR: data is NULL\n");
		return (0);
	}
	if (!data->scene)
	{
		printf("ERROR: data->scene is NULL\n");
		return (0);
	}
	if (!data->scene->player)
	{
		printf("ERROR: data->scene->player is NULL\n");
		return (0);
	}
	return (1);
}

int	key_press(int keycode, t_cub_data *data)
{
	double	move_speed;
	double	rotation_speed;

	if (!validate_data(data))
		return (1);
	move_speed = 0.3;
	rotation_speed = 0.1;
	if (keycode == KEY_ESC)
		exit_game(data);
	if (keycode == KEY_W)
		move_forward_backward(data, data->scene->player, move_speed);
	else if (keycode == KEY_S)
		move_forward_backward(data, data->scene->player, -move_speed);
	else if (keycode == KEY_A)
		move_left_right(data, data->scene->player, -move_speed);
	else if (keycode == KEY_D)
		move_left_right(data, data->scene->player, move_speed);
	else if (keycode == KEY_LEFT)
		rotate_player(data->scene->player, rotation_speed);
	else if (keycode == KEY_RIGHT)
		rotate_player(data->scene->player, -rotation_speed);
	render_scene(data, data->scene);
	mlx_put_image_to_window(data->scene->draw->mlx_connection,
		data->scene->draw->mlx_window, data->scene->draw->img->img_ptr, 0, 0);
	return (0);
}

int	close_window(t_cub_data *data)
{
	exit_game(data);
	return (0);
}
