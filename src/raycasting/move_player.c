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

void	move_forward(t_player *player, t_game *game, float angle, float speed)
{
	float	new_x;
	float	new_y;
	float	cos_a;
	float	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	new_x = player->x + cos_a * speed;
	new_y = player->y + sin_a * speed;
	if (!touch(new_x, player->y, game))
		player->x = new_x;
	if (!touch(player->x, new_y, game))
		player->y = new_y;
}

void	move_backward(t_player *player, t_game *game, float angle, float speed)
{
	float	new_x;
	float	new_y;
	float	cos_a;
	float	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	new_x = player->x - cos_a * speed;
	new_y = player->y - sin_a * speed;
	if (!touch(new_x, player->y, game))
		player->x = new_x;
	if (!touch(player->x, new_y, game))
		player->y = new_y;
}

void	move_left(t_player *player, t_game *game, float side_a, float speed)
{
	float	new_x;
	float	new_y;

	new_x = player->x - cos(side_a) * speed;
	new_y = player->y - sin(side_a) * speed;
	if (!touch(new_x, player->y, game))
		player->x = new_x;
	if (!touch(player->x, new_y, game))
		player->y = new_y;
}

void	move_right(t_player *player, t_game *game, float side_a, float speed)
{
	float	new_x;
	float	new_y;

	new_x = player->x + cos(side_a) * speed;
	new_y = player->y + sin(side_a) * speed;
	if (!touch(new_x, player->y, game))
		player->x = new_x;
	if (!touch(player->x, new_y, game))
		player->y = new_y;
}

void	move_player(t_player *player, t_game *game)
{
	float	speed;
	float	angle_speed;
	float	side_angle;

	speed = 3.5;
	angle_speed = 0.05;
	rotate_player(player, angle_speed);
	side_angle = player->angle + PI / 2;
	if (player->key_up)
		move_forward(player, game, player->angle, speed);
	if (player->key_down)
		move_backward(player, game, player->angle, speed);
	if (player->key_left)
		move_left(player, game, side_angle, speed);
	if (player->key_right)
		move_right(player, game, side_angle, speed);
}
