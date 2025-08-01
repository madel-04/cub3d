/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:31:50 by madel-va          #+#    #+#             */
/*   Updated: 2025/06/02 13:31:50 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(int color[3])
{
	return (color[0] << 16 | color[1] << 8 | color[2]);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;
	int	floor_color;
	int	ceiling_color;

	y = 0;
	floor_color = get_rgb(game->config.floor_color);
	ceiling_color = get_rgb(game->config.ceiling_color);
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			if (y < game->win_height / 2)
				put_pixel(&game->img, x, y, ceiling_color);
			else
				put_pixel(&game->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}









void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return;
	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}


void	my_mlx_area_put(t_img *img, int x, int y, int w, int h, int color)
{
	int i = 0;
	while (i < h)
	{
		int j = 0;
		while (j < w)
		{
			my_mlx_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

#define TILE_SIZE 6

enum e_map_colors {
	MAP_WALL = 0x333333,     // gris oscuro
	MAP_FLOOR = 0xAAAAAA,    // gris claro
	MAP_EMPTY = 0x000000,    // negro
	MAP_PLAYER = 0x00AFFF    // azul cielo
};

void	draw_minimap(t_game *game)
{
	int	map_y = 0;

	while (game->config.map_lines[map_y])
	{
		int	map_x = 0;
		while (game->config.map_lines[map_y][map_x])
		{
			char	tile = game->config.map_lines[map_y][map_x];
			int		color;

			if (tile == '1')
				color = MAP_WALL;
			else if (tile == '0')
				color = MAP_FLOOR;
			else if (tile == ' ')
				color = MAP_EMPTY;
			else if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
				color = MAP_PLAYER;
			else
				color = 0xFF0000; // rojo para caracteres desconocidos

			for (int dy = 0; dy < TILE_SIZE; dy++)
			{
				for (int dx = 0; dx < TILE_SIZE; dx++)
				{
					int px = map_x * TILE_SIZE + dx;
					int py = map_y * TILE_SIZE + dy;
					if (px < game->minimap.width && py < game->minimap.height)
						*(unsigned int *)(game->minimap.data
							+ py * game->minimap.size_line + px * 4) = color;
				}
			}
			map_x++;
		}
		map_y++;
	}

	// Pintar jugador
	int	player_px = (int)(game->player.x * TILE_SIZE);
	int	player_py = (int)(game->player.y * TILE_SIZE);
	for (int dy = -2; dy <= 2; dy++)
	{
		for (int dx = -2; dx <= 2; dx++)
		{
			int px = player_px + dx;
			int py = player_py + dy;
			if (px >= 0 && py >= 0 && px < game->minimap.width && py < game->minimap.height)
				*(unsigned int *)(game->minimap.data
					+ py * game->minimap.size_line + px * 4) = MAP_PLAYER;
		}
	}
}




void	draw_vertical_line(t_game *game, int x, int y_start, int y_end, int color)
{
	int y = y_start;
	while (y <= y_end)
	{
		*(unsigned int *)(game->img.data + y * game->img.size_line + x * 4) = color;
		y++;
	}
}

void	render_raycast(t_game *game)
{
	int x = 0;
	while (x < game->win_width)
	{
		// Aquí luego irá el cálculo de raycasting real
		int line_height = game->win_height / 2;

		int draw_start = -line_height / 2 + game->win_height / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + game->win_height / 2;
		if (draw_end >= game->win_height)
			draw_end = game->win_height - 1;

		draw_vertical_line(game, x, draw_start, draw_end, 0xFFFFFF);
		x++;
	}
}

int	render_frame(t_game *game)
{
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, game->win_width,
			game->win_height);
	game->img.data = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.size_line, &game->img.endian);
	game->img.width = game->win_width;
	game->img.height = game->win_height;
	draw_background(game);
	render_raycast(game);
	// Aquí luego irá raycasting...


	// Actualiza el minimapa antes de dibujarlo
	draw_minimap(game);

	// Muestra el frame principal
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);

	// Superpone el minimapa en la esquina superior izquierda
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->minimap.img_ptr, 20, 20);

	mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
	return (0);
}
