/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:00:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/10 18:37:46 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

bool	touch(float px, float py, t_game *game)
{
		int x, y;
		static int *map_widths = NULL;
		static int last_height = -1;
		x = px / BLOCK;
		y = py / BLOCK;
		if (!game->config.map_lines)
			return (true);
		int height = ft_strarray_len(game->config.map_lines);
		if (!map_widths || last_height != height) {
			if (map_widths)
				free(map_widths);
			map_widths = malloc(sizeof(int) * height);
			for (int i = 0; i < height; i++)
				map_widths[i] = ft_strlen(game->config.map_lines[i]);
			last_height = height;
		}
		if (y < 0 || y >= height || !game->config.map_lines[y])
			return (true);
		if (x < 0 || x >= map_widths[y])
			return (true);
		return (game->config.map_lines[y][x] == '1');
}

void	put_pixel_newversion(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->img.size_line + x * game->img.bpp / 8;
	game->img.data[index] = color & 0xFF;
	game->img.data[index + 1] = (color >> 8) & 0xFF;
	game->img.data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, t_square *square, t_game *game)
{
	int	i;

	i = 0;
	while (i < square->size)
	{
		put_pixel_newversion(x + i, y, square->color, game);
		put_pixel_newversion(x + i, y + square->size - 1, square->color, game);
		i++;
	}
	i = 1;
	while (i < square->size - 1)
	{
		put_pixel_newversion(x, y + i, square->color, game);
		put_pixel_newversion(x + square->size - 1, y + i, square->color, game);
		i++;
	}
}
