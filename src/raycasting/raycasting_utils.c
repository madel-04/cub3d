/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:00:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/06 03:20:57 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int rgb_to_int(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

float distance(float x, float y)
{
    return sqrt(x * x + y * y);
}

bool touch(float px, float py, t_game *game)
{
    int x = px / BLOCK;
    int y = py / BLOCK;

    // Validación de límites del mapa
    if (y < 0 || !game->config.map_lines[y])
        return true;

    if (x < 0 || x >= (int)ft_strlen(game->config.map_lines[y]))
        return true;

    return (game->config.map_lines[y][x] == '1');
}

void   put_pixel_newversion(int x, int y, int color, t_game *game)
{
    int index;
    
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;

    index = y * game->img.size_line + x * game->img.bpp / 8;
    game->img.data[index] = color & 0xFF;
    game->img.data[index + 1] = (color >> 8) & 0xFF;
    game->img.data[index + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
    int i = 0;
    while (i < size)
    {
        put_pixel_newversion(x + i, y, color, game); // Top
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel_newversion(x + i, y + size - 1, color, game); // Bottom
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel_newversion(x, y + i, color, game); // Left
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel_newversion(x + size - 1, y + i, color, game); // Right
        i++;
    }
}
