/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:49:55 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/08 05:26:08 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	charge_textures(t_game *game)
{
	game->config.north = load_texture(game->mlx_ptr,
			"./textures/greystone.xpm");
	game->config.south = load_texture(game->mlx_ptr,
			"./textures/purplestone.xpm");
	game->config.east = load_texture(game->mlx_ptr, "./textures/redbrick.xpm");
	game->config.west = load_texture(game->mlx_ptr, "./textures/wood.xpm");
	return (1);
}

void	set_player_angle(t_player *player, char **map, t_spawn_info info)
{
	player->x = (info.x + 0.5) * BLOCK;
	player->y = (info.y + 0.5) * BLOCK;
	if (info.c == 'N')
		player->angle = 3 * PI / 2;
	else if (info.c == 'S')
		player->angle = PI / 2;
	else if (info.c == 'E')
		player->angle = 0;
	else if (info.c == 'W')
		player->angle = PI;
	map[info.y][info.x] = '0';
}

void	get_map_dimensions(t_game *game, int *map_width, int *map_height)
{
	int	len;

	*map_width = 0;
	*map_height = 0;
	while (game->config.map_lines[*map_height])
	{
		len = ft_strlen(game->config.map_lines[*map_height]);
		if (len > *map_width)
			*map_width = len;
		(*map_height)++;
	}
}

void	rotate_player(t_player *player, float angle_speed)
{
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
}
