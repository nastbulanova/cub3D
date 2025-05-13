#include "../../inc/functions.h"

t_texture	*add_wall_pixels(t_draw *draw, char* file)
{
	t_texture	*temp_tex;

	temp_tex = NULL;
	temp_tex = (t_texture *)malloc(sizeof(t_texture));
	if (!temp_tex)
		return (NULL);
	temp_tex->img_ptr = mlx_xpm_file_to_image (draw->mlx_connection , file, 
                                               &temp_tex->width , &temp_tex->height) ;
	if (!temp_tex->img_ptr)
		return (free(temp_tex), NULL);
	temp_tex->pixels = mlx_get_data_addr(temp_tex->img_ptr,
							&temp_tex->bpp, &temp_tex->line_length, &temp_tex->endian);
	return (temp_tex);
}

t_textures	*load_textures(t_draw *draw, t_map *map)
{
	t_textures *texs;

	texs = (t_textures *)malloc(sizeof(t_textures));
	if (!texs)
		return (NULL);
	texs->north = NULL;
	texs->north = add_wall_pixels(draw, map->file_no);
	if (!texs->north)
		return (free(texs), NULL);
	texs->south = NULL;
	texs->south = add_wall_pixels(draw, map->file_so);
	if (!texs->south)
		return (NULL);//add free
	texs->east = NULL;
	texs->east = add_wall_pixels(draw, map->file_ea);
	if (!texs->east)
		return (NULL);//add free
	texs->west = NULL;
	texs->west = add_wall_pixels(draw, map->file_we);
	if (!texs->west)
		return (NULL);//add free
	return (texs);
}

t_draw	*draw_init(void)
{
	t_draw *draw;

	draw = NULL;
	draw = (t_draw *)malloc(sizeof(t_draw));
	if (!draw)
		return (NULL);
	draw->mlx_connection = mlx_init();
	draw->mlx_window = mlx_new_window (draw->mlx_connection , WINDOW_WIDTH , WINDOW_HEIGHT , "cub3D");
	draw->img = NULL;
	draw->img = (t_img *)malloc(sizeof(t_img));
	if (!draw->img)
		return (free(draw), NULL);
	draw->img->img_ptr = mlx_new_image(draw->mlx_connection,
							WINDOW_WIDTH, WINDOW_HEIGHT);
	draw->img->pixels = mlx_get_data_addr(draw->img->img_ptr, &draw->img->bpp,
							&draw->img->line_length, &draw->img->endian);
	return (draw);
}

t_scene	*render_init(t_cub_data *data, t_map *map)
{
	t_scene *scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->draw = NULL;
	scene->draw = draw_init();
	if (!scene->draw)
		return (free(scene), NULL);
	scene->player = NULL;
	scene->cols = data->cols;
	scene->rows = data->rows;
	scene->fov_scale = get_fov_scale();
	scene->floor = rgb_to_color(&(data->floor));
	scene->ceil = rgb_to_color(&(data->ceil));
	scene->texs = NULL;
	scene->texs = load_textures(scene->draw, map);
	if (!scene->texs)
		return (NULL);// add free(scene and draw)
	return (scene);
}
