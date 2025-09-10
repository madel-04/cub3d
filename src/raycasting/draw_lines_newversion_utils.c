/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines_newversion_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:35:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/10 19:35:00 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_player *p, t_game *g, float angle, t_draw_data *data)
{
		float ca = cos(angle);
		float sa = sin(angle);
		float step = 0.25f; // Menor step para mayor precisión y menos saltos
		data->rx = p->x;
		data->ry = p->y;
		// El bucle solo avanza, no recalcula trigonometría
		while (!touch(data->rx, data->ry, g)) {
			data->rx += ca * step;
			data->ry += sa * step;
			// Si quieres limitar la distancia máxima, añade aquí un break
		}
		data->rx += ca * step;
		data->ry += sa * step;
}


void	compute_wall(t_draw_data *data, t_game *g)
{
	float	dist;

	dist = real_distance(data->rx, data->ry, g);
	data->wh = (BLOCK / dist) * (WIDTH / 2);
	data->sy = (HEIGHT - data->wh) / 2;
}

t_texture	*get_face_texture(t_game *g, t_face_texture *face)
{
	char	**map;

	map = g->config.map_lines;
	if (face->my > 0 && map[face->my - 1] && face->mx
		< (int)ft_strlen(map[face->my - 1])
		&& map[face->my - 1][face->mx] == '0' && face->ly < 1.0f)
		return (&g->config.south);
	if (map[face->my + 1] && face->mx < (int)ft_strlen(map[face->my + 1])
		&& map[face->my + 1][face->mx] == '0' && face->ly > BLOCK - 1.0f)
		return (&g->config.north);
	if (face->mx > 0 && face->mx - 1 < (int)ft_strlen(map[face->my])
		&& map[face->my][face->mx - 1] == '0' && face->lx < 1.0f)
		return (&g->config.east);
	if (face->mx + 1 < (int)ft_strlen(map[face->my])
		&& map[face->my][face->mx + 1] == '0' && face->lx > BLOCK - 1.0f)
		return (&g->config.west);
	return (&g->config.north);
}

t_texture	*select_texture(t_game *g, float rx, float ry, int *tx)
{
	t_face_texture	face;
	t_texture		*tex;

	face.mx = (int)(rx / BLOCK);
	face.my = (int)(ry / BLOCK);
	face.lx = rx - face.mx * BLOCK;
	face.ly = ry - face.my * BLOCK;
	tex = get_face_texture(g, &face);
	if (tex == &g->config.north || tex == &g->config.south)
		*tx = (int)(face.lx / BLOCK * tex->width);
	else
		*tx = (int)(face.ly / BLOCK * tex->width);
	if (*tx < 0)
		*tx = 0;
	if (*tx >= tex->width)
		*tx = tex->width - 1;
	return (tex);
}

void	draw_column(int col, t_draw_data *data, t_game *g)
{
	int	y;
	int	ey;
	int	ty;
	int	color;

	ey = data->sy + data->wh;
	y = data->sy;
	while (y < ey && y < HEIGHT)
	{
		ty = (int)((float)(y - data->sy) * data->tex->height / data->wh);
		if (ty < 0)
			ty = 0;
		if (ty >= data->tex->height)
			ty = data->tex->height - 1;
		color = data->tex->pixels[ty * data->tex->width + data->tx];
		put_pixel_newversion(col, y, color, g);
		y++;
	}
}
