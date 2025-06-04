/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:27:55 by suroh             #+#    #+#             */
/*   Updated: 2025/06/04 14:04:25 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/functions.h"

static size_t	find_maxlen(char **raw, int rows)
{
	size_t	i;
	size_t	len;
	size_t	max;

	max = 0;
	i = 0;
	while (i < (size_t)rows)
	{
		len = 0;
		while (raw[i][len])
			len++;
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	**alloc_grid(int rows, int cols)
{
	char	**grid;
	int		i;
	t_map	*map;

	(void)map;
	grid = malloc(sizeof(*grid) * rows);
	if (!grid)
		exit_error(NULL, "malloc failed");
	i = 0;
	while (i < rows)
	{
		grid[i] = malloc(cols + 1);
		if (!grid[i])
			exit_error(NULL, "malloc failed");
		i++;
	}
	return (grid);
}

static void	fill_grid(char **grid, char **raw, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (raw[i][j])
		{
			grid[i][j] = raw[i][j];
			j++;
		}
		while (j < cols)
			grid[i][j++] = ' ';
		grid[i][j] = '\0';
		i++;
	}
}

static void	free_raw(char **raw, int rows)
{
	int	i;

	i = -1;
	while (++i < rows)
		free(raw[i]);
	free(raw);
}

char	**finalize_grid(char **raw, int rows, int *out_cols)
{
	size_t	maxlen;
	char	**grid;

	maxlen = find_maxlen(raw, rows);
	*out_cols = (int)maxlen;
	grid = alloc_grid(rows, *out_cols);
	fill_grid(grid, raw, rows, *out_cols);
	free_raw(raw, rows);
	return (grid);
}

/*
 * 1) Find the maximum string length in the ragged array
 * size_t	find_maxlen(char **raw, int rows)
 *
 * 2) Allocate the rectangular grid pointers
 * char	**alloc_grid(int rows, int cols)
 *
 * 3) Copy raw lines into grid, padding with spaces
 * void	fill_grid(char **grid, char **raw, int rows, int cols)
 *
 * 4) Free the old ragged raw array
 * void	free_raw(char **raw, int rows)
 *
 * Top-level that uses the helpers
 * char	**finalize_grid(char **raw, int rows, int *out_cols)
 *
 */
