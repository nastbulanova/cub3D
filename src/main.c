/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:54:12 by suroh             #+#    #+#             */
/*   Updated: 2025/06/04 19:48:24 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/functions.h"

int	handle_keypress(int keysym, void *param)
{
	t_cub_data	*data;

	data = (t_cub_data *)param;
	if (keysym == XK_Escape)
		return (exit_game(data));
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
		exit_error(NULL, "Cannot open map file");
	map = init_map_struct();
	grid = NULL;
	rows = 0;
	read_map_lines(fd, map);
	close(fd);
	grid = map->map;
	rows = map->rows;
	map->map = finalize_grid(grid, rows, &map->cols);
	map->rows = rows;
	validate_map(map);
	return (map);
}

int	main(int argc, char **argv)
{
	t_map		*map;
	t_cub_data	*data;

	if (argc != 2)
		exit_error(NULL, "Usage: ./cub3D <map.cub>");
	map = parse_map(argv[1]);
	data = data_init(map);
	render_scene(data, data->scene);
	mlx_put_image_to_window(data->scene->draw->mlx_connection,
		data->scene->draw->mlx_window, data->scene->draw->img->img_ptr,
		0, 0);
	mlx_hook(data->scene->draw->mlx_window,
		KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->scene->draw->mlx_window,
		KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->scene->draw->mlx_window, 17, 0,
		close_window, data);
	mlx_loop_hook(data->scene->draw->mlx_connection, loop_hook, data);
	mlx_loop(data->scene->draw->mlx_connection);
	return (0);
}
