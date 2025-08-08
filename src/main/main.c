/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:00:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/08 05:35:38 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
	return (0);
}

int	ft_ends_with(const char *str, const char *suffix)
{
	int	len_str;
	int	len_suf;

	len_str = ft_strlen(str);
	len_suf = ft_strlen(suffix);
	if (len_str < len_suf)
		return (0);
	return (ft_strncmp(str + len_str - len_suf, suffix, len_suf) == 0);
}

void	textures_and_hooks(t_game *game, t_config *config)
{
	config->north = load_texture(game->mlx_ptr, config->textures[0]);
	config->south = load_texture(game->mlx_ptr, config->textures[1]);
	config->west = load_texture(game->mlx_ptr, config->textures[2]);
	config->east = load_texture(game->mlx_ptr, config->textures[3]);
	mlx_hook(game->win_ptr, 2, 1L << 0, key_press_newversion, &game->player);
	mlx_hook(game->win_ptr, 3, 1L << 1, key_release_newversion, &game->player);
	mlx_hook(game->win_ptr, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx_ptr, draw_loop_newversion, game);
}

void	cleanup(t_game *game, t_config *config)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free_config(config);
	free_game(game);
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_game		game;
	int			fd;

	if (argc != 2 || !ft_ends_with(argv[1], ".cub"))
		return (ft_error("Error: uso -> ./cub3D mapa.cub\n"), 1);
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
		return (close(fd), ft_error("Error: no puede ser un directorio.\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_error("Error: no se pudo abrir el archivo.\n"), 1);
	ft_config_init(&config);
	if (!ft_parse_config(fd, &config) || !config.map_lines)
		return (ft_error("Error al parsear configuración o mapa vacío.\n"), 1);
	if (!validate_config(&config, &game))
		return (free_config(&config), ft_error("Error: configuración\n"), 1);
	close(fd);
	if (!init_game_newversion(&game, &config))
		return (free_config(&game.config), ft_error("Error al iniciar\n"), 1);
	textures_and_hooks(&game, &config);
	mlx_loop(game.mlx_ptr);
	cleanup(&game, &config);
	return (0);
}

/*
Rroadmap:
X Parseo completo (.cub)

X Validaciones de mapa

X Convertir mapa a formato interno

X Inicializar jugador y MiniLibX

X Implementar raycasting

X Añadir controles y render loop
*/