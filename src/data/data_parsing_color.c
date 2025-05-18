/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parsing_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:45:10 by suroh             #+#    #+#             */
/*   Updated: 2025/05/18 19:49:23 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/structs.h"
#include "../../libs/libft/libft.h"

static void	free_split_array(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static void	extract_rgb_values(char **split, t_rgb *color)
{
	int	i;

	i = 0;
	while (split[i] && i < 3)
	{
		if (i == 0)
			color->red = ft_atoi(split[i]);
		else if (i == 1)
			color->green = ft_atoi(split[i]);
		else if (i == 2)
			color->blue = ft_atoi(split[i]);
		i++;
	}
}

t_rgb	parse_color_string(char *color_str)
{
	t_rgb	color;
	char	**split;

	color.red = 0;
	color.green = 0;
	color.blue = 0;
	if (!color_str)
		return (color);
	split = ft_split(color_str, ',');
	if (!split)
		return (color);
	extract_rgb_values(split, &color);
	free_split_array(split);
	return (color);
}
