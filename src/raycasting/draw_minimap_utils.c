/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:00:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/10 12:32:48 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(int x, int y, int width, int height, int color,
		t_game *game)
{
	int	j;
	int	i;

	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			put_pixel_newversion(x + i, y + j, color, game);
			i++;
		}
		j++;
	}
}

void	fill_square(int x, int y, int size, int color, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_newversion(x + i, y + j, color, game);
			j++;
		}
		i++;
	}
}

void	draw_background_cell(char c, int x, int y, t_game *game, int offset_x,
		int offset_y)
{
	t_square	square;

	square.size = MINI_BLOCK;
	square.color = 0x00FF00;
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		fill_square(x * MINI_BLOCK + offset_x, y * MINI_BLOCK + offset_y,
			MINI_BLOCK, 0x444444, game);
		if (c == '1')
			draw_square(x * MINI_BLOCK + offset_x, y * MINI_BLOCK + offset_y,
				&square, game);
	}
}

void	draw_map_background(t_game *game, int offset_x, int offset_y)
{
	int		x;
	int		y;
	char	**map;

	map = game->config.map_lines;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			draw_background_cell(map[y][x], x, y, game, offset_x, offset_y);
			x++;
		}
		y++;
	}
}

void	draw_single_ray(float angle, t_game *game, int offset_x, int offset_y)
{
	float	ray_x;
	float	ray_y;
	float	cos_a;
	float	sin_a;
	int		mini_x;
	int		mini_y;

	ray_x = game->player.x;
	ray_y = game->player.y;
	cos_a = cos(angle);
	sin_a = sin(angle);
	while (!touch(ray_x, ray_y, game))
	{
		mini_x = ray_x / BLOCK * MINI_BLOCK + offset_x;
		mini_y = ray_y / BLOCK * MINI_BLOCK + offset_y;
		put_pixel_newversion(mini_x, mini_y, 0xAAAAAA, game);
		ray_x += cos_a;
		ray_y += sin_a;
	}
}
