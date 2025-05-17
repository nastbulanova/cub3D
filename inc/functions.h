/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:32:25 by suroh             #+#    #+#             */
/*   Updated: 2025/05/17 22:51:57 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "defines.h"
# include "structs.h"

//render
void			put_pixel(t_img *img, int x, int y, int color);
void			draw_ceil_floor(t_scene *scene);
void			draw_column(t_scene *scene, t_texture *tex, int draw_start,
					int draw_end, int tex_x, double step, int x);
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
t_draw			*draw_init(void);
t_scene			*render_init(t_cub_data *data, t_map *map);

//render_init_utils
float			get_fov_scale(void);
int				rgb_to_color(t_rgb *color);

//parsing
t_map			*init_map_struct(void);
bool			is_texture_line(char *line);
bool			is_map_line(char *line);
void			parse_texture_line(t_map *map, char *line);
void			parse_color_line(char **target, char *line);
void			add_map_line(char *line, char ***grid, int *rows);
void			process_line(t_map *map, char *line, char ***grid, int *rows);
void			read_map_lines(int fd, t_map *map, char ***grid, int *rows);

//finalize_grid
char			**finalize_grid(char **raw, int rows, int *out_cols);

//validate_map
void			validate_map(t_map *map);

//helpers
void			exit_error(char *msg);
void			ft_free_split(char **arr);
char			**realloc_list(char **list, int new_count);

#endif
