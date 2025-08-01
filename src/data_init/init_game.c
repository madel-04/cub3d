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

int	init_game(t_game *game, t_config *config)
{
	int	screen_width;
	int	screen_height;

	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (ft_error("Error al inicializar mlx\n"));
	mlx_get_screen_size(game->mlx_ptr, &screen_width, &screen_height);
	game->win_width = screen_width;
	game->win_height = screen_height;
	game->config = *config;
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->win_width,
			game->win_height, "Cub3D");
	if (!game->win_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		return (ft_error("Error al crear la ventana\n"));
	}
	ft_init_player(game, config->map_lines);


	int map_width = 0;
	int map_height = 0;
	while (game->config.map_lines[map_height])
	{
		if ((int)ft_strlen(game->config.map_lines[map_height]) > map_width)
			map_width = ft_strlen(game->config.map_lines[map_height]);
		map_height++;
	}

	int tile_size = 6;

	game->minimap.width = map_width * tile_size;
	game->minimap.height = map_height * tile_size;
	game->minimap.img_ptr = mlx_new_image(game->mlx_ptr, game->minimap.width, game->minimap.height);
	game->minimap.data = mlx_get_data_addr(game->minimap.img_ptr, &game->minimap.bpp,
	&game->minimap.size_line, &game->minimap.endian);

	return (1);
}

static void	set_player_orientation(t_game *game, char dir)
{
	if (dir == 'N')
		set_orientation_north(game);
	else if (dir == 'S')
		set_orientation_south(game);
	else if (dir == 'E')
		set_orientation_east(game);
	else if (dir == 'W')
		set_orientation_west(game);
}

static int	set_player_position(t_game *game, char **map, int i, int j)
{
	char	dir;

	dir = map[i][j];
	game->player.x = j + 0.5;
	game->player.y = i + 0.5;
	set_player_orientation(game, dir);
	return (0);
}

int	ft_init_player(t_game *game, char **map_lines)
{
	int	i;
	int	j;

	i = 0;
	while (map_lines[i])
	{
		j = 0;
		while (map_lines[i][j])
		{
			if (map_lines[i][j] == 'N' || map_lines[i][j] == 'S' ||
				map_lines[i][j] == 'E' || map_lines[i][j] == 'W')
				return (set_player_position(game, map_lines, i, j));
			j++;
		}
		i++;
	}
	return (ft_error("Error: No se encontró el jugador en el mapa\n"));
}
