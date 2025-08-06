/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:00:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/06 04:08:03 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float real_distance(float ray_x, float ray_y, t_game *game)
{
    float delta_x = ray_x - game->player.x;
    float delta_y = ray_y - game->player.y;
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float real_dist = distance(delta_x, delta_y) * cos(angle);
    
    return real_dist;
}

void clear_image_newversion(t_game *game)
{
    int x, y;
    int floor_color = rgb_to_int(game->config.floor_color[0], game->config.floor_color[1], game->config.floor_color[2]);
    int ceiling_color = rgb_to_int(game->config.ceiling_color[0], game->config.ceiling_color[1], game->config.ceiling_color[2]);

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

void draw_lines_newversion(t_player *player, t_game *game, float ray_angle, int column)
{
    float ray_x = player->x;
    float ray_y = player->y;
    float cos_angle = cos(ray_angle);
    float sin_angle = sin(ray_angle);

    while (!touch(ray_x, ray_y, game))
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
    }

    float dist = real_distance(ray_x, ray_y, game);
    float wall_height = (BLOCK / dist) * (WIDTH / 2);
    int start_y = (HEIGHT - wall_height) / 2;
    int end_y = start_y + wall_height;

    // Coordenadas del bloque impactado
    int map_x = (int)(ray_x / BLOCK);
    int map_y = (int)(ray_y / BLOCK);
    t_texture *tex = NULL;
    char **map = game->config.map_lines;

    // Coordenadas locales dentro del bloque
    float local_x = ray_x - map_x * BLOCK;
    float local_y = ray_y - map_y * BLOCK;

    // Determinar cara tocada comprobando los bloques adyacentes
    // y la posición local del impacto dentro del bloque
    if (map_y > 0 && map[map_y - 1] && map_x < (int)ft_strlen(map[map_y - 1]) &&
    map[map_y - 1][map_x] == '0' && local_y < 1.0f)
        tex = &game->config.south;  // cara SUR (superior del bloque)
    else if (map[map_y + 1] && map_x < (int)ft_strlen(map[map_y + 1]) &&
         map[map_y + 1][map_x] == '0' && local_y > BLOCK - 1.0f)
        tex = &game->config.north;
    else if (map_x > 0 && map_x - 1 < (int)ft_strlen(map[map_y]) &&
            map[map_y][map_x - 1] == '0' && local_x < 1.0f)
        tex = &game->config.east;
    else if (map_x + 1 < (int)ft_strlen(map[map_y]) &&
            map[map_y][map_x + 1] == '0' && local_x > BLOCK - 1.0f)
        tex = &game->config.west;   // cara OESTE (derecha)
    else
        tex = &game->config.north; // fallback

    // Calcular coordenada horizontal de la textura (depende del tipo de cara tocada)
    int tex_x;
    if (tex == &game->config.north || tex == &game->config.south)
        tex_x = (int)(local_x / BLOCK * tex->width);
    else
        tex_x = (int)(local_y / BLOCK * tex->width);

    if (tex_x < 0) tex_x = 0;
    if (tex_x >= tex->width) tex_x = tex->width - 1;

    // Pintar columna vertical
    int y = start_y;
    while (y < end_y && y < HEIGHT)
    {
        int tex_y = (int)((float)(y - start_y) * tex->height / wall_height);
        if (tex_y < 0) tex_y = 0;
        if (tex_y >= tex->height) tex_y = tex->height - 1;

        int color = tex->pixels[tex_y * tex->width + tex_x];
        put_pixel_newversion(column, y, color, game);
        y++;
    }
}


int draw_loop_newversion(t_game *game)
{
    t_player *player;

    player = &game->player;
    move_player(player, game);
    clear_image_newversion(game);

    float fraction = PI / 3 / WIDTH;
    float start_x = player->angle - PI / 6;
    int i = 0;
    while (i < WIDTH)
    {
        draw_lines_newversion(player, game, start_x, i);
        start_x += fraction;
        i++;
    } 
    if (player->show_minimap)
        draw_minimap_newversion(game);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);

    return 0;
}
