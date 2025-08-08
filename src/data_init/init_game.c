/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:49:55 by madel-va          #+#    #+#             */
/*   Updated: 2025/06/02 12:49:55 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_newversion(t_player *player)
{
	player->x = WIDTH / 2 - BLOCK / 4;
	player->y = HEIGHT / 2 - BLOCK / 4;
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->show_minimap = false;
}

void	init_player_from_map(t_player *player, char **map)
{
	int				y;
	int				x;
	t_spawn_info	info;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				info.x = x;
				info.y = y;
				info.c = map[y][x];
				set_player_angle(player, map, info);
				return ;
			}
			x++;
		}
		y++;
	}
}

int	init_window_and_images(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (0);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (!game->win_ptr)
		return (0);
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	if (!game->img.img_ptr)
		return (0);
	game->img.data = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.size_line, &game->img.endian);
	if (!game->img.data)
		return (0);
	return (1);
}

int	init_minimap(t_game *game, int map_width, int map_height, int tile_size)
{
	game->minimap.width = map_width * tile_size;
	game->minimap.height = map_height * tile_size;
	game->minimap.img_ptr = mlx_new_image(game->mlx_ptr, game->minimap.width,
			game->minimap.height);
	if (!game->minimap.img_ptr)
		return (0);
	game->minimap.data = mlx_get_data_addr(game->minimap.img_ptr,
			&game->minimap.bpp, &game->minimap.size_line,
			&game->minimap.endian);
	if (!game->minimap.data)
		return (0);
	return (1);
}

int	init_game_newversion(t_game *game, t_config *config)
{
	int	map_width;
	int	map_height;
	int	tile_size;

	tile_size = 6;
	game->config = *config;
	init_player_newversion(&game->player);
	init_player_from_map(&game->player, game->config.map_lines);
	if (!init_window_and_images(game))
		return (0);
	if (!charge_textures(game))
		return (0);
	get_map_dimensions(game, &map_width, &map_height);
	if (!init_minimap(game, map_width, map_height, tile_size))
		return (0);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0,
		0);
	return (1);
}
