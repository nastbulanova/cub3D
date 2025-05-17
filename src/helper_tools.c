/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:43:30 by suroh             #+#    #+#             */
/*   Updated: 2025/05/17 22:49:40 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/functions.h"
#include "../libs/libft/libft.h"

void	exit_error(char *msg)
{
	ssize_t	ignored;

	ignored = write(2, "Error\n", 6);
	(void)ignored;
	ignored = write(2, msg, ft_strlen(msg));
	(void)ignored;
	ignored = write(2, "\n", 1);
	(void)ignored;
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
