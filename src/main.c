#include "../inc/functions.h"

int	handle_keypress(int keysym, void *param)
{
	(void)param;
	if (keysym == XK_Escape)
		exit(0);
	return (0);
}

t_map	*parse_map(void)
{
	t_map		*map;

	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return (NULL);

	//here should be parsing
	//but now it's just to run the program
	map->cols = 10;
	map->rows = 6;
	map->map = (char**)malloc(sizeof(char*) * map->rows);
	if (!map->map)
		return (NULL); //here will be clean up
	map->map[0] = "1111111111";
	map->map[1] = "1000100001";
	map->map[2] = "1000100011";
	map->map[3] = "1110001111";
	map->map[4] = "1000000001";
	map->map[5] = "1111111111";
	map->file_ea = "./files/bluestone.xpm";
	map->file_no = "./files/colorstone.xpm";
	map->file_so = "./files/greystone.xpm";
	map->file_we = "./files/purplestone.xpm";
	return (map);
}

t_player	*player_init(void)
{
	t_player	*player;

	player = (t_player*)malloc(sizeof(t_player));
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
	data = (t_cub_data*)malloc(sizeof(t_cub_data));
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

int	main()
{
	t_map		*map;
	t_cub_data	*data;

	map = NULL;
	map = parse_map();
	if (!map)
		return (1); //here will be clean up
	data = NULL;
	data = data_init(map);
	if (!data)
		return (1); //here will be clean up
	render_scene(data, data->scene);
	mlx_put_image_to_window(data->scene->draw->mlx_connection, data->scene->draw->mlx_window,
							data->scene->draw->img->img_ptr, 0, 0);
	mlx_hook(data->scene->draw->mlx_window, KeyPress, KeyPressMask, handle_keypress, NULL);
	mlx_loop(data->scene->draw->mlx_connection);
}