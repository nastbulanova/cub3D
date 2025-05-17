/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:39:26 by suroh             #+#    #+#             */
/*   Updated: 2024/11/26 17:09:56 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size != 0)
	{
		i = 0;
		while (i < (size - 1) && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	char	*mem;
	size_t	len;

	len = ft_strlen(s);
	mem = (char *)malloc(len + 1);
	if (!mem)
		return (NULL);
	mem[len] = '\0';
	while (len--)
		mem[len] = s[len];
	return (mem);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*mem;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	mem = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!mem)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		mem[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		mem[i] = s2[j];
		i++;
		j++;
	}
	mem[i] = '\0';
	return (mem);
}
