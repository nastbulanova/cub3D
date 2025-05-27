/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:33:54 by suroh             #+#    #+#             */
/*   Updated: 2025/05/27 15:06:53 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

static bool	handle_movement(t_cub_data *data, double mv)
{
	bool	moved;

	moved = false;
	if (data->keys.forward)
	{
		move_forward_backward(data, data->scene->player, mv);
		moved = true;
	}
	if (data->keys.back)
	{
		move_forward_backward(data, data->scene->player, -mv);
		moved = true;
	}
	if (data->keys.left)
	{
		move_left_right(data, data->scene->player, -mv);
		moved = true;
	}
	if (data->keys.right)
	{
		move_left_right(data, data->scene->player, mv);
		moved = true;
	}
	return (moved);
}

static bool	handle_rotation(t_cub_data *data, double rt)
{
	bool	moved;

	moved = false;
	if (data->keys.turn_left)
	{
		rotate_player(data->scene->player, rt);
		moved = true;
	}
	if (data->keys.turn_right)
	{
		rotate_player(data->scene->player, -rt);
		moved = true;
	}
	return (moved);
}

int	loop_hook(t_cub_data *data)
{
	bool	moved;
	bool	m1;
	bool	m2;
	float	mv;
	float	rt;

	mv = 0.005;
	rt = 0.002;
	m1 = handle_movement(data, mv);
	m2 = handle_rotation(data, rt);
	moved = (m1 || m2);
	if (moved)
		update_display(data);
	return (0);
}
