/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:30:37 by suroh             #+#    #+#             */
/*   Updated: 2025/05/18 22:53:37 by suroh            ###   ########.fr       */
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
		exit_error("Invalid resolution line");
	w = ft_atoi(tok[0]);
	h = ft_atoi(tok[1]);
	ft_free_split(tok);
	if (map->res_w != 0 || map->res_h != 0)
		exit_error("Duplicate resolution");
	if (w <= 0 || h <= 0)
		exit_error("Resolution must be positive");
	map->res_w = w;
	map->res_h = h;
}

void	parse_texture_line(t_map *map, char *line)
{
	char	*path;

	path = ft_strdup(line + 3);
	if (!path)
		exit_error("malloc failed");
	if (ft_strncmp(line, "NO ", 3) == 0)
		map->file_no = path;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map->file_so = path;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map->file_we = path;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map->file_ea = path;
	else
		exit_error("Unknown texture identifier");
}
