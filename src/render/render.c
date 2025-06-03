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

int get_rgb(int color[3])
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
	int	x, y;
	int	floor_color = get_rgb(game->config.floor_color);
	int	ceiling_color = get_rgb(game->config.ceiling_color);

	y = 0;
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

int	render_frame(t_game *game)
{
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, game->win_width, game->win_height);
	game->img.data = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.size_line, &game->img.endian);
	game->img.width = game->win_width;
	game->img.height = game->win_height;

	draw_background(game);
	// Aquí luego irá raycasting...

	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
	mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
	return (0);
}
