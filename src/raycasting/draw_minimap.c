/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:00:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/10 18:42:13 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_rays(t_game *game, int offset_x, int offset_y)
{
	float	fraction;
	float	angle;
	int		i;

	fraction = PI / 3 / WIDTH;
	angle = game->player.angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		if (i % 10 == 0)
			draw_single_ray(angle, game, offset_x, offset_y);
		angle += fraction;
		i++;
	}
}

void	draw_minimap_mini(t_game *game, int offset_x, int offset_y)
{
	int			px;
	int			py;
	t_square	square;

	square.size = MINI_PLAYER_SIZE;
	square.color = 0xFF0000;
	px = game->player.x / BLOCK * MINI_BLOCK + offset_x - 2;
	py = game->player.y / BLOCK * MINI_BLOCK + offset_y - 2;
	draw_map_background(game, offset_x, offset_y);
	draw_square(px, py, &square, game);
	draw_minimap_rays(game, offset_x, offset_y);
}

void	get_map_block_size(t_game *game, int *width, int *height)
{
	int		len;
	int		max_width;
	int		y;
	char	**map;

	max_width = 0;
	y = 0;
	map = game->config.map_lines;
	while (map[y])
	{
		len = ft_strlen(map[y]);
		if (len > max_width)
			max_width = len;
		y++;
	}
	*width = max_width;
	*height = y;
}

void	draw_minimap_newversion(t_game *game)
{
	int	map_width;
	int	map_height;
	int	offset_x;
	int	offset_y;

	get_map_block_size(game, &map_width, &map_height);
	offset_x = (WIDTH - (map_width * MINI_BLOCK)) / 2;
	offset_y = (HEIGHT - (map_height * MINI_BLOCK)) / 2;
	draw_minimap_mini(game, offset_x, offset_y);
}
