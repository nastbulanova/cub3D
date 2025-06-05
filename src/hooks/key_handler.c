/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:40:03 by suroh             #+#    #+#             */
/*   Updated: 2025/06/05 20:17:26 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

int	exit_game(t_cub_data *data)
{
	if (!data)
		return (0);
	if (data->mlx && data->win)
		mlx_destroy_window(data->mlx, data->win);
	free_scene(data->mlx, data->scene);
	free(data);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_cub_data *data)
{
	if (keycode == KEY_W)
		data->keys.forward = true;
	else if (keycode == KEY_S)
		data->keys.back = true;
	else if (keycode == KEY_A)
		data->keys.left = true;
	else if (keycode == KEY_D)
		data->keys.right = true;
	else if (keycode == KEY_LEFT)
		data->keys.turn_left = true;
	else if (keycode == KEY_RIGHT)
		data->keys.turn_right = true;
	else if (keycode == KEY_ESC)
		return (exit_game(data));
	return (0);
}

int	key_release(int keycode, t_cub_data *data)
{
	if (keycode == KEY_W)
		data->keys.forward = false;
	else if (keycode == KEY_S)
		data->keys.back = false;
	else if (keycode == KEY_A)
		data->keys.left = false;
	else if (keycode == KEY_D)
		data->keys.right = false;
	else if (keycode == KEY_LEFT)
		data->keys.turn_left = false;
	else if (keycode == KEY_RIGHT)
		data->keys.turn_right = false;
	return (0);
}

int	close_window(t_cub_data *data)
{
	return (exit_game(data));
}
