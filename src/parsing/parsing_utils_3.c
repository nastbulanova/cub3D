/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:30:37 by suroh             #+#    #+#             */
/*   Updated: 2025/06/04 20:45:47 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"
#include "../../libs/libft/libft.h"

static void	set_no(char *path, char *line, t_map *map)
{
	if (map->file_no)
	{
		free(path);
		free(line);
		exit_error(map, "Duplicate NO texture");
	}
	map->file_no = path;
}

static void	set_so(char *path, char *line, t_map *map)
{
	if (map->file_so)
	{
		free(path);
		free(line);
		exit_error(map, "Duplicate SO texture");
	}
	map->file_so = path;
}

static void	set_we(char *path, char *line, t_map *map)
{
	if (map->file_we)
	{
		free(path);
		free(line);
		exit_error(map, "Duplicate WE texture");
	}
	map->file_we = path;
}

static void	set_ea(char *path, char *line, t_map *map)
{
	if (map->file_ea)
	{
		free(path);
		free(line);
		exit_error(map, "Duplicate EA texture");
	}
	map->file_ea = path;
}

void	parse_texture_line(t_map *map, char *line)
{
	char	*path;

	path = ft_strdup(line + 3);
	if (!path)
		exit_error(map, "malloc failed in parse_texture_line");
	if (!ft_strncmp(line, "NO ", 3))
		set_no(path, line, map);
	else if (!ft_strncmp(line, "SO ", 3))
		set_so(path, line, map);
	else if (!ft_strncmp(line, "WE ", 3))
		set_we(path, line, map);
	else if (!ft_strncmp(line, "EA ", 3))
		set_ea(path, line, map);
	else
	{
		free(path);
		free(line);
		exit_error(map, "Unknown texture identifier");
	}
}
