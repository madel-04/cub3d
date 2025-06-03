/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:49:55 by madel-va          #+#    #+#             */
/*   Updated: 2025/06/02 12:49:55 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_game(t_game *game, t_config *config)
{
	game->win_width = 800;
	game->win_height = 600;
	game->config = *config;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (ft_error("Error al inicializar mlx\n")); // Error initializing MLX
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->win_width, game->win_height, "Cub3D");
	if (!game->win_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		return (ft_error("Error al crear la ventana\n")); // Error creating window
	}
	ft_init_player(game, config->map_lines);

	return (1);
}

int	ft_init_player(t_game *game, char **map_lines)
{
	int i;
	int j;

	i = 0;
	while (map_lines[i])
	{
		j = 0;
		while (map_lines[i][j])
		{
			if (map_lines[i][j] == 'N' || map_lines[i][j] == 'S' ||
				map_lines[i][j] == 'E' || map_lines[i][j] == 'W')
			{
				game->player.x = j + 0.5; // Player position
				game->player.y = i + 0.5;
				if (map_lines[i][j] == 'N')
				{
					game->player.dir_x = 0;
					game->player.dir_y = -1;
					game->player.plane_x = 0.66;
					game->player.plane_y = 0;
				}
				else if (map_lines[i][j] == 'S')
				{
					game->player.dir_x = 0;
					game->player.dir_y = 1;
					game->player.plane_x = -0.66;
					game->player.plane_y = 0;
				}
				else if (map_lines[i][j] == 'E')
				{
					game->player.dir_x = 1;
					game->player.dir_y = 0;
					game->player.plane_x = 0;
					game->player.plane_y = 0.66;
				}
				else if (map_lines[i][j] == 'W')
				{
					game->player.dir_x = -1;
					game->player.dir_y = 0;
					game->player.plane_x = 0;
					game->player.plane_y = -0.66;
				}
				return (0);
			}
			j++;
		}
		i++;
	}
	return (ft_error("Error: No se encontró el jugador en el mapa\n")); // Player not found in map
}
