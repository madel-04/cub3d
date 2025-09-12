/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:54:59 by madel-va          #+#    #+#             */
/*   Updated: 2025/06/10 21:54:59 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_newversion(int keycode, t_player *player)
{
	if (keycode == KEY_W)
		player->key_up = true;
	if (keycode == KEY_S)
		player->key_down = true;
	if (keycode == KEY_A)
		player->key_left = true;
	if (keycode == KEY_D)
		player->key_right = true;
	if (keycode == KEY_LEFT)
		player->left_rotate = true;
	if (keycode == KEY_RIGHT)
		player->right_rotate = true;
	if (keycode == KEY_SPACE)
		player->show_minimap = !player->show_minimap;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	key_release_newversion(int keycode, t_player *player)
{
	if (keycode == KEY_W)
		player->key_up = false;
	if (keycode == KEY_S)
		player->key_down = false;
	if (keycode == KEY_A)
		player->key_left = false;
	if (keycode == KEY_D)
		player->key_right = false;
	if (keycode == KEY_LEFT)
		player->left_rotate = false;
	if (keycode == KEY_RIGHT)
		player->right_rotate = false;
	return (0);
}
