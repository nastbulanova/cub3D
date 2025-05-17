/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:35:15 by suroh             #+#    #+#             */
/*   Updated: 2025/05/17 21:26:30 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"
#include "../../libs/libft/libft.h"

t_map	*init_map_struct(void)
{
	t_map	*map;

	map = malloc(sizeof(*map));
	if (!map)
		exit_error("malloc failed");
	map->cols = 0;
	map->rows = 0;
	map->map = NULL;
	map->file_no = NULL;
	map->file_so = NULL;
	map->file_we = NULL;
	map->file_ea = NULL;
	map->floor = NULL;
	map->ceil = NULL;
	return (map);
}

bool	is_texture_line(char *line)
{
	return (
		ft_strncmp(line, "NO", 3) == 0
		|| ft_strncmp(line, "SO", 3) == 0
		|| ft_strncmp(line, "WE", 3) == 0
		|| ft_strncmp(line, "EA", 3) == 0
	);
}

bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (false);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (line[i] == '1');
}
