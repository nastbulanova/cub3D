/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:32:25 by suroh             #+#    #+#             */
/*   Updated: 2025/06/04 20:08:50 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "defines.h"
# include "structs.h"

//render
void			put_pixel(t_img *img, int x, int y, int color);
void			draw_ceil_floor(t_scene *scene);
void			draw_column(t_scene *scene, t_texture *tex, t_ray *ray);
void			render_column(t_cub_data *data, t_scene *scene, int x);
void			render_scene(t_cub_data *data, t_scene *scene);

//render_ray_utils
void			calculate_ray(t_scene *scene, int x, t_ray *ray);
void			init_ray_steps(t_scene *scene, t_ray *ray, int *map_x,
					int *map_y);
void			perform_dda(t_cub_data *data, t_ray *ray, int *map_x,
					int *map_y);
double			calculate_wall_distance(t_scene *scene, t_ray *ray, int map_x,
					int map_y);

//render_tex_utils
int				calculate_tex_x(t_scene *scene, double perp_dist, t_ray *ray,
					t_texture *tex);
void			calculate_projection(double perp_dist, int *line_height,
					int *draw_start, int *draw_end);
t_texture		*choose_texture(t_scene *scene, t_ray *ray);
unsigned int	get_tex_pixel(t_texture *tex, int x, int y);

//render_init
t_texture		*add_wall_pixels(t_draw *draw, char *file);
t_textures		*load_textures(t_draw *draw, t_map *map);
t_draw			*draw_init(t_map *map);
t_scene			*render_init(t_cub_data *data, t_map *map);

//render_init_utils
float			get_fov_scale(void);
int				rgb_to_color(t_rgb *color);
void			set_dimensions(t_map *map, int *width, int *height);
int				init_image(t_draw *draw, int width, int height);
int				setup_draw_and_textures(t_scene *scene, t_map *map);
t_scene			*init_scene_basics(t_cub_data *data, t_map *map);

//player
void			set_player_directions(t_player *player, char direction);
char			find_player_position(t_map *map, int *x_pos, int *y_pos);
t_player		*player_init(t_map *map);
void			move_forward_backward(t_cub_data *data,
					t_player *player, double speed);
void			move_left_right(t_cub_data *data,
					t_player *player, double speed);
void			rotate_player(t_player *player, double angle);

//key_hooks
int				exit_game(t_cub_data *data);
void			free_map_data(t_map *map);
void			free_textures(void *mlx, t_textures *textures);
void			free_drawing_resources(void *mlx, t_draw *draw);
void			free_scene(void *mlx, t_scene *scene);
int				key_press(int keycode, t_cub_data *data);
int				key_release(int keycode, t_cub_data *data);
int				close_window(t_cub_data *data);
void			handle_movement_keys(int keycode, t_cub_data *data,
					double move_speed);
void			handle_rotation_keys(int keycode, t_cub_data *data,
					double rot_speed);
void			update_display(t_cub_data *data);
int				loop_hook(t_cub_data *data);

//data
t_cub_data		*data_init(t_map *map);
t_rgb			parse_color_string(char *color_str);

//parsing
t_map			*init_map_struct(void);
bool			is_texture_line(char *line);
bool			is_map_line(char *line);
bool			is_blank_line(char *line);
char			*strip_line(const char *line);
void			parse_texture_line(t_map *map, char *line);
void			parse_color_line(char **target, char *line);
void			add_map_line(t_map *map, char *line, char ***grid, int *rows);
void			process_line(t_map *map, char *line, char ***grid, int *rows);
void			read_map_lines(int fd, t_map *map);
void			parse_resolution_line(t_map *map, char *line);

//finalize_grid
char			**finalize_grid(char **raw, int rows, int *out_cols);

//validate_map
void			validate_map(t_map *map);
void			check_char(t_map *map);

//helpers
void			exit_error(t_map *map, char *msg);
void			ft_free_split(char **arr);
char			**realloc_list(char **list, int new_count);
void			cleanup_partial_data(t_cub_data *data);

#endif
