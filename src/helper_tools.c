/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:43:30 by suroh             #+#    #+#             */
/*   Updated: 2025/06/04 19:48:47 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/functions.h"
#include "../libs/libft/libft.h"
#include "../libs/get_next_line/get_next_line.h"

void	exit_error(t_map *map, char *msg)
{
	if (map)
		free_map_data(map);
	g_nl_cleanup();
	if (msg)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd((char *)msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd("Error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**realloc_list(char **list, int new_count)
{
	char	**new_list;
	int		i;

	new_list = malloc(sizeof(char *) * (new_count + 1));
	if (!new_list)
		return (NULL);
	new_list[new_count] = NULL;
	i = 0;
	while (list && i < new_count - 1)
	{
		new_list[i] = list[i];
		i++;
	}
	free(list);
	return (new_list);
}

void	cleanup_partial_data(t_cub_data *data)
{
	if (data->player)
		free(data->player);
	free(data);
}
