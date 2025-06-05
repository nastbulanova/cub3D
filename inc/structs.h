/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:31:11 by suroh             #+#    #+#             */
/*   Updated: 2025/06/05 20:11:11 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "defines.h"

typedef struct s_map
{
	char	*file_no;
	char	*file_so;
	char	*file_we;
	char	*file_ea;
	char	*floor;
	char	*ceil;
	char	**map;
	int		cols;
	int		rows;
	int		res_w;
	int		res_h;
	int		fd_cub;
}			t_map;

typedef struct s_player
{
	double	d_x;
	double	d_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
}				t_player;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

typedef struct s_keys
{
	bool	forward;
	bool	back;
	bool	left;
	bool	right;
	bool	turn_left;
	bool	turn_right;
}				t_keys;

typedef struct s_cub_data
{
	void			*mlx;
	void			*win;
	t_rgb			floor;
	t_rgb			ceil;
	char			**map;
	int				cols;
	int				rows;
	t_player		*player;
	struct s_scene	*scene;
	t_keys			keys;
}				t_cub_data;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_texture
{
	void	*img_ptr;
	char	*pixels;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}				t_texture;

typedef struct s_draw
{
	void	*mlx_connection;
	void	*mlx_window;
	t_img	*img;
}				t_draw;

typedef struct s_textures
{
	t_texture	*north;
	t_texture	*south;
	t_texture	*east;
	t_texture	*west;
}				t_textures;

typedef struct s_scene
{
	t_draw		*draw;
	t_map		*map;
	t_player	*player;
	t_textures	*texs;
	double		plane_x;
	double		plane_y;
	int			cols;
	int			rows;
	float		fov_scale;
	int			floor;
	int			ceil;
}				t_scene;

typedef struct s_map_pos
{
	int		x;
	int		y;
}				t_map_pos;

typedef struct s_projection
{
	double	perp_dist;
	int		line_height;
}				t_projection;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	tex_step;
	int		screen_x;
	double	tex_pos;

}				t_ray;

#endif
