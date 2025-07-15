/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:50:39 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/28 22:50:39 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_closed(char **map)
{
	char	**copy;
	int		x;
	int		y;
	int		valid;

	copy = copy_map(map);
	if (!copy)
		return (ft_error("Error al copiar mapa\n"));
	if (!find_player_start(copy, &x, &y))
	{
		free_map(copy);
		return (ft_error("No hay jugador en el mapa\n"));
	}
	valid = flood_fill(copy, x, y);
	free_map(copy);
	if (!valid)
		return (ft_error("El mapa tiene huecos o está abierto.\n"));
	return (1);
}

char	**copy_map(char **map)
{
	int		i;
	char	**copy;
	int		j;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	j = 0;
	while (j < i)
	{
		copy[j] = ft_strdup(map[j]);
		j++;
	}
	copy[i] = NULL;
	return (copy);
}

int	find_player_start(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i++])
	{
		j = 0;
		while (map[i][j++])
		{
			if (ft_strchr("0NSEW", map[i][j]))
			{
				*x = j;
				*y = i;
				return (1);
			}
		}
	}
	return (0);
}

int	flood_fill(char **map, int x, int y)
{
	if (y < 0 || x < 0 || map[y] == NULL || x >= (int)ft_strlen(map[y])
		|| map[y][x] == ' ')
	{
		printf("Out of bounds: x=%d, y=%d\n", x, y);
		return (0);
	}
	if (ft_strchr("X1", map[y][x]))
		return (1);
	map[y][x] = 'X';
	return (flood_fill(map, x + 1, y)
		&& flood_fill(map, x - 1, y)
		&& flood_fill(map, x, y + 1)
		&& flood_fill(map, x, y - 1));
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}
