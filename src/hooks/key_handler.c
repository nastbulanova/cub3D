/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:40:03 by suroh             #+#    #+#             */
/*   Updated: 2025/05/19 22:12:10 by suroh            ###   ########.fr       */
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

	if (!data || !validate_data(data))
		return (1);
	move_speed = 0.3;
	rotation_speed = 0.1;
	if (keycode == KEY_ESC)
		exit_game(data);
	handle_movement_keys(keycode, data, move_speed);
	handle_rotation_keys(keycode, data, rotation_speed);
	update_display(data);
	return (0);
}

int	close_window(t_cub_data *data)
{
	exit_game(data);
	return (0);
}
