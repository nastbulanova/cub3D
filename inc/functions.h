#ifndef FUNCTIONS_H
#define FUNCTIONS_H

# include "defines.h"
# include "structs.h"

//render
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_ceil_floor(t_scene *scene);
void	draw_column(t_scene *scene, t_texture *tex, int draw_start,
					int draw_end, int tex_x, double step, int x);
void	render_column(t_cub_data *data, t_scene *scene, int x);
void	render_scene(t_cub_data *data, t_scene *scene);

//render_ray_utils
void	calculate_ray(t_scene *scene, int x, t_ray *ray);
void	init_ray_steps(t_scene *scene, t_ray *ray, int *map_x, int *map_y);
void	perform_dda(t_cub_data *data, t_ray *ray, int *map_x, int *map_y);
double	calculate_wall_distance(t_scene *scene, t_ray *ray, int map_x, int map_y);

//render_tex_utils
unsigned int	get_tex_pixel(t_texture *tex, int x, int y);
void			calculate_projection(double perp_dist, int *line_height, int *draw_start, int *draw_end);
t_texture		*choose_texture(t_scene *scene, t_ray *ray);
int				calculate_tex_x(t_scene *scene, double perp_dist, t_ray *ray,
				   t_texture *tex);

//render_init
t_texture	*add_wall_pixels(t_draw *draw, char *file);
t_textures	*load_textures(t_draw *draw, t_map *map);
t_draw		*draw_init(void);
t_scene		*render_init(t_cub_data *data, t_map *map);

//render_init_utils
float	get_fov_scale(void);
int		rgb_to_color(t_rgb *color);

#endif
