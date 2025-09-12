/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:00:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/10 19:56:47 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch(float px, float py, t_game *game)
{
	int			x;
	int			y;
	int			height;
	static int	*map_widths;
	static int	last_height;

	x = px / BLOCK;
	y = py / BLOCK;
	if (!game->config.map_lines)
		return (true);
	height = ft_strarray_len(game->config.map_lines);
	if (!map_widths || last_height != height)
	{
		last_height = touch_free_map_widths(&map_widths, &height, game);
	}
	if (y < 0 || y >= height || !game->config.map_lines[y])
		return (true);
	if (x < 0 || x >= map_widths[y])
		return (true);
	return (game->config.map_lines[y][x] == '1');
}

float	real_distance(float ray_x, float ray_y, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	real_dist;

	delta_x = ray_x - game->player.x;
	delta_y = ray_y - game->player.y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	real_dist = distance(delta_x, delta_y) * cos(angle);
	return (real_dist);
}

void	clear_image_newversion(t_game *game)
{
	int	floor_color;
	int	ceiling_color;
	int	x;
	int	y;

	floor_color = rgb_to_int(game->config.floor_color[0],
			game->config.floor_color[1], game->config.floor_color[2]);
	ceiling_color = rgb_to_int(game->config.ceiling_color[0],
			game->config.ceiling_color[1], game->config.ceiling_color[2]);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel_newversion(x, y, ceiling_color, game);
			else
				put_pixel_newversion(x, y, floor_color, game);
			x++;
		}
		y++;
	}
}

// ********************************************************* //
void	draw_lines_newversion(t_player *player, t_game *game, float a, int col)
{
	t_draw_data	data;

	init_ray(player, game, a, &data);
	compute_wall(&data, game);
	data.tex = select_texture(game, data.rx, data.ry, &data.tx);
	draw_column(col, &data, game);
}

// *********************************************** //

int	draw_loop_newversion(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	move_player(player, game);
	clear_image_newversion(game);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_lines_newversion(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	if (player->show_minimap)
		draw_minimap_newversion(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0,
		0);
	return (0);
}
