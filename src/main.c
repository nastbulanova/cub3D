/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:54:12 by suroh             #+#    #+#             */
/*   Updated: 2025/05/17 22:42:03 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/functions.h"

int	handle_keypress(int keysym, void *param)
{
	(void)param;
	if (keysym == XK_Escape)
		exit(0);
	return (0);
}

t_map	*parse_map(char *file_path)
{
	int		fd;
	char	**grid;
	t_map	*map;
	int		rows;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit_error("Cannot open map file");
	map = init_map_struct();
	grid = NULL;
	rows = 0;
	read_map_lines(fd, map, &grid, &rows);
	close(fd);
	map->map = finalize_grid(grid, rows, &map->cols);
	map->rows = rows;
	validate_map(map);
	return (map);
}

t_player	*player_init(void)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	//should be parsed
	player->pos_x = 1.5;
	player->pos_y = 1.5;
	player->d_x = 1;
	player->d_y = 0;
	return (player);
}

t_cub_data	*data_init(t_map *map)
{
	t_cub_data	*data;

	data = NULL;
	data = (t_cub_data *)malloc(sizeof(t_cub_data));
	if (!data)
		return (NULL);
	data->player = NULL;
	data->player = player_init();
	if (!data->player)
		return (NULL); //need to free data
	data->map = map->map;
	data->cols = map->cols;
	data->rows = map->rows;
	//should be parsed
	data->floor.red = 220;
	data->floor.green = 100;
	data->floor.blue = 0;
	data->ceil.red = 225;
	data->ceil.green = 30;
	data->ceil.blue = 0;
	data->scene = NULL;
	data->scene = render_init(data, map);
	if (!data->scene)
		return (NULL); //need to free data
	return (data);
}

int	main(int argc, char **argv)
{
	t_map		*map;
	t_cub_data	*data;

	if (argc != 2)
		exit_error("Usage: ./cub3D <map.cub>");
	map = parse_map(argv[1]);
	data = data_init(map);
	render_scene(data, data->scene);
	mlx_put_image_to_window(data->scene->draw->mlx_connection,
		data->scene->draw->mlx_window, data->scene->draw->img->img_ptr,
		0, 0);
	mlx_hook(data->scene->draw->mlx_window,
		KeyPress, KeyPressMask, handle_keypress, NULL);
	mlx_loop(data->scene->draw->mlx_connection);
	return (0);
}
