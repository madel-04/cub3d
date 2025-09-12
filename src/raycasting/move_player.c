/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:00:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/09 20:39:50 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement(t_player *player, float *dx, float *dy)
{
	if (player->key_up)
	{
		*dx += cos(player->angle);
		*dy += sin(player->angle);
	}
	if (player->key_down)
	{
		*dx -= cos(player->angle);
		*dy -= sin(player->angle);
	}
	if (player->key_left)
	{
		*dx += cos(player->angle - PI / 2);
		*dy += sin(player->angle - PI / 2);
	}
	if (player->key_right)
	{
		*dx += cos(player->angle + PI / 2);
		*dy += sin(player->angle + PI / 2);
	}
}

static void	get_player_movement_and_coords(t_player *player, float speed,
		float *new_x, float *new_y)
{
	float	dx;
	float	dy;

	dx = 0;
	dy = 0;
	movement(player, &dx, &dy);
	if ((player->key_up || player->key_down)
		&& (player->key_left || player->key_right))
	{
		dx /= 1.41421356f;
		dy /= 1.41421356f;
	}
	*new_x = player->x + dx * speed;
	*new_y = player->y + dy * speed;
}

void	move_player(t_player *player, t_game *game)
{
	float	speed;
	float	angle_speed;
	float	new_x;
	float	new_y;

	speed = 2.15;
	angle_speed = 0.025;
	rotate_player(player, angle_speed);
	get_player_movement_and_coords(player, speed, &new_x, &new_y);
	if (!touch(new_x, player->y, game))
		player->x = new_x;
	if (!touch(player->x, new_y, game))
		player->y = new_y;
}
