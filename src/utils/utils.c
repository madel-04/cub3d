/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:05:52 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/29 21:00:35 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(const char *message)
{
	if (message)
	{
		write(2, "Error\n", 6);
		write(2, message, ft_strlen(message));
	}
	exit(EXIT_FAILURE);
}

char	**ft_realloc_strarray(char **old, int old_count, int new_alloc)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * (new_alloc + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < old_count)
	{
		new_arr[i] = old[i];
		i++;
	}
	new_arr[i] = NULL;
	free(old);
	return (new_arr);
}

void	free_strarray(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_strarray_free(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_strarray_len(char **arr)
{
	int	count;

	count = 0;
	if (!arr)
		return (0);
	while (arr[count])
		count++;
	return (count);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r'
		|| c == '\f' || c == '\v' )
		return (1);
	return (0);
}

char	*ft_strdup_textures(const char *s)
{
	char	*dest;
	size_t	i;

	if (!s)
		return (NULL);
	dest = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}