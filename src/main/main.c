/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:00:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/07/31 17:57:25 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	config;
	int			fd;
	t_game		game;

	if (argc != 2)
		return (ft_putstr_fd("Error: Número incorrecto de argumentos.\n", 2), 1);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
		return (ft_putstr_fd("Error: El archivo debe tener extensión .cub\n", 2), 1);
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (ft_putstr_fd("Error: El archivo no puede ser un directorio.\n",
				2), 1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (ft_putstr_fd("Error: No se pudo abrir el archivo.\n", 2), 1);
	}
	ft_config_init(&config);
	if (!ft_parse_config(fd, &config))
	{
		ft_error("Error al parsear la configuración.\n");
		return (1);
	}

	if (!config.map_lines)
	{
		ft_error("Error: mapa no cargado tras parseo.\n");
		return (1);
	}
	if (!validate_config(&config, &game))
	{
		free_config(&config);
		return (ft_error("Error: Configuración inválida.\n"));
	}
	close(fd);
	if (!init_game_newversion(&game, &config))
	{
		free_config(&game.config);
		return (ft_error("Error: Fallo al inicializar el juego.\n"));
	}
	config.north = load_texture(game.mlx_ptr, config.textures[0]);
	config.south = load_texture(game.mlx_ptr, config.textures[1]);
	config.west  = load_texture(game.mlx_ptr, config.textures[2]);
	config.east  = load_texture(game.mlx_ptr, config.textures[3]);
	
	mlx_hook(game.win_ptr, 2, 1L<<0, key_press_newversion, &game.player);        	 // Key press
	mlx_hook(game.win_ptr, 3, 1L<<1, key_release_newversion, &game.player);	 // Key release
	mlx_hook(game.win_ptr, 17, 0, close_window, &game);

	mlx_loop_hook(game.mlx_ptr, draw_loop_newversion, &game);
	mlx_loop(game.mlx_ptr);
	
	mlx_destroy_window(game.mlx_ptr, game.win_ptr);
	mlx_destroy_display(game.mlx_ptr);
	free(game.mlx_ptr);
	free_config(&config);
	free_game(&game);
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