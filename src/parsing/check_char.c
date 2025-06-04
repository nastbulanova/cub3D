/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:06:43 by suroh             #+#    #+#             */
/*   Updated: 2025/06/04 20:42:49 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"
#include "../../libs/libft/libft.h"

void	parse_resolution_line(t_map *map, char *line)
{
	char	**tok;
	int		w;
	int		h;

	tok = ft_split(line + 1, ' ');
	if (!tok || !tok[0] || !tok[1] || tok[2])
		exit_error(map, "Invalid resolution line");
	w = ft_atoi(tok[0]);
	h = ft_atoi(tok[1]);
	ft_free_split(tok);
	if (map->res_w != 0 || map->res_h != 0)
		exit_error(map, "Duplicate resolution");
	if (w <= 0 || h <= 0)
		exit_error(map, "Resolution must be positive");
	map->res_w = w;
	map->res_h = h;
}

void	check_char(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			c = map->map[y][x];
			if (c != '0'
				&& c != '1'
				&& c != 'N' && c != 'S' && c != 'E' && c != 'W'
				&& c != ' ')
				exit_error(map, "Invalid character in map");
			x++;
		}
		y++;
	}
}
