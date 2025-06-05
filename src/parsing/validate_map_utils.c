/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:57:06 by suroh             #+#    #+#             */
/*   Updated: 2025/06/05 19:58:45 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

void	validate_texture_path(t_map *map, char *path)
{
	int	fd;

	if (!path)
		exit_error(map, "Missing texture path");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_error(map, "Cannot open texture file");
	close(fd);
}
