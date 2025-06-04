/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:43:27 by suroh             #+#    #+#             */
/*   Updated: 2025/06/04 20:48:13 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "../libs/minilibx-linux/mlx.h"
# include "X11/X.h"
# include "X11/keysym.h"
# include <ctype.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 860
# define MVSPEED 0.0085
# define RTSPEED 0.0055
# define FOV 60
# define PI_CONST 3.14159265358979323846
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65363
# define KEY_RIGHT 65361

#endif
