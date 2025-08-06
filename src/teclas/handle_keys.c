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

int	handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		exit(0);
	}
	if (keycode == KEY_W)
		game->player.move_forward = 1;
	if (keycode == KEY_S)
		game->player.move_backward = 1;
	if (keycode == KEY_A)
		game->player.move_left = 1;
	if (keycode == KEY_D)
		game->player.move_right = 1;
	if (keycode == KEY_LEFT)
		game->player.turn_left = 1;
	if (keycode == KEY_RIGHT)
		game->player.turn_right = 1;
	printf("%i\n", game->player.move_forward);
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.move_forward = 0;
	if (keycode == KEY_S)
		game->player.move_backward = 0;
	if (keycode == KEY_A)
		game->player.move_left = 0;
	if (keycode == KEY_D)
		game->player.move_right = 0;
	if (keycode == KEY_LEFT)
		game->player.turn_left = 0;
	if (keycode == KEY_RIGHT)
		game->player.turn_right = 0;
	printf("%i\n", game->player.move_forward);
	return (0);
}

int key_press_newversion(int keycode, t_player *player)
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
    if (keycode == KEY_SPACE) // define KEY_M como desees, por ejemplo 46
        player->show_minimap = !player->show_minimap;
    if (keycode == KEY_ESC)
        exit(0);

    return 0;
}

int key_release_newversion(int keycode, t_player *player)
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
    return 0;
}
