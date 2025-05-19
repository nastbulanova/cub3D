/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:32:28 by suroh             #+#    #+#             */
/*   Updated: 2025/05/18 22:53:20 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

void	move_forward_backward(t_cub_data *data, t_player *player, double speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->d_x * speed;
	new_y = player->pos_y + player->d_y * speed;
	if (data->map[(int)player->pos_y][(int)new_x] != '1')
		player->pos_x = new_x;
	if (data->map[(int)new_y][(int)player->pos_x] != '1')
		player->pos_y = new_y;
}

/*void move_forward_backward(t_cub_data *data, t_player *player, double speed)
{
    double new_x;
    double new_y;

    printf("MOVE FB: Current pos=(%f,%f) dir=(%f,%f) speed=%f\n", 
        player->pos_x, player->pos_y, player->d_x, player->d_y, speed);

    new_x = player->pos_x + player->d_x * speed;
    new_y = player->pos_y + player->d_y * speed;
    
    printf("MOVE FB: Attempting to move to (%f,%f)\n", new_x, new_y);
    
    // Check X collision
    if (data->map[(int)player->pos_y][(int)new_x] != '1')
    {
        player->pos_x = new_x;
        printf("MOVE FB: X move allowed\n");
    }
    else
    {
        printf("MOVE FB: X collision detected at map[%d][%d] = '%c'\n", 
            (int)player->pos_y, (int)new_x,
			data->map[(int)player->pos_y][(int)new_x]);
    }
    
    // Check Y collision
    if (data->map[(int)new_y][(int)player->pos_x] != '1')
    {
        player->pos_y = new_y;
        printf("MOVE FB: Y move allowed\n");
    }
    else
    {
        printf("MOVE FB: Y collision detected at map[%d][%d] = '%c'\n", 
            (int)new_y, (int)player->pos_x,
			data->map[(int)new_y][(int)player->pos_x]);
    }
    
    printf("MOVE FB: Final position = (%f,%f)\n", player->pos_x, player->pos_y);
}
*/

void	move_left_right(t_cub_data *data, t_player *player, double speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->plane_x * speed;
	new_y = player->pos_y + player->plane_y * speed;
	if (data->map[(int)player->pos_y][(int)new_x] != '1')
		player->pos_x = new_x;
	if (data->map[(int)new_y][(int)player->pos_x] != '1')
		player->pos_y = new_y;
}

void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->d_x;
	old_plane_x = player->plane_x;
	player->d_x = player->d_x * cos(angle) - player->d_y * sin(angle);
	player->d_y = old_dir_x * sin(angle) + player->d_y * cos(angle);
	player->plane_x
		= player->plane_x * cos(angle) - player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}
