/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_inits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:00:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/06 03:59:34 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void set_player_angle(t_player *player, char **map, int x, int y, char c)
{
    player->x = (x + 0.5) * BLOCK;
    player->y = (y + 0.5) * BLOCK;
    if (c == 'N')
        player->angle = 3 * PI / 2;
    else if (c == 'S')
        player->angle = PI / 2;
    else if (c == 'E')
        player->angle = 0;
    else if (c == 'W')
        player->angle = PI;
    map[y][x] = '0';
}

void init_player_from_map(t_player *player, char **map)
{
    int y;
    int x;
    char c;

    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            c = map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                set_player_angle(player, map, x, y, c);
                return;
            }
            x++;
        }
        y++;
    }
}


int init_window_and_images(t_game *game)
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
    game->img.data = mlx_get_data_addr(game->img.img_ptr,
        &game->img.bpp, &game->img.size_line, &game->img.endian);
    if (!game->img.data)
        return (0);
    return (1);
}

int init_textures(t_game *game)
{
    game->config.north = load_texture(game->mlx_ptr, "./textures/greystone.xpm");
    game->config.south = load_texture(game->mlx_ptr, "./textures/purplestone.xpm");
    game->config.east = load_texture(game->mlx_ptr, "./textures/redbrick.xpm");
    game->config.west = load_texture(game->mlx_ptr, "./textures/wood.xpm");
    return (1);
}

void get_map_dimensions(t_game *game, int *map_width, int *map_height)
{
    int len;
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

int init_minimap(t_game *game, int map_width, int map_height, int tile_size)
{
    game->minimap.width = map_width * tile_size;
    game->minimap.height = map_height * tile_size;
    game->minimap.img_ptr = mlx_new_image(game->mlx_ptr,
        game->minimap.width, game->minimap.height);
    if (!game->minimap.img_ptr)
        return (0);
    game->minimap.data = mlx_get_data_addr(game->minimap.img_ptr,
        &game->minimap.bpp, &game->minimap.size_line, &game->minimap.endian);
    if (!game->minimap.data)
        return (0);
    return (1);
}

void init_player_newversion(t_player *player)
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

int init_game_newversion(t_game *game, t_config *config)
{
    int map_width;
    int map_height;
    int tile_size;

    tile_size = 6;
    game->config = *config;
    init_player_newversion(&game->player);
    init_player_from_map(&game->player, game->config.map_lines);
    if (!init_window_and_images(game))
        return (0);
    if (!init_textures(game))
        return (0);
    get_map_dimensions(game, &map_width, &map_height);
    if (!init_minimap(game, map_width, map_height, tile_size))
        return (0);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
    return (1);
}
