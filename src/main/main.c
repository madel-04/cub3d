/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 10:00:00 by madel-va          #+#    #+#             */
/*   Updated: 2025-05-28 10:00:00 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_config	config;
	int			fd;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Número incorrecto de argumentos.\n", 2);
		return (1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error: El archivo debe tener extensión .cub\n", 2);
		return (1);
	}
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_putstr_fd("Error: El archivo no puede ser un directorio.\n", 2);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		ft_putstr_fd("Error: No se pudo abrir el archivo.\n", 2);
		return (1);
	}
	ft_config_init(&config); // & Inicializar la configuración 
	if (!ft_parse_config(fd, &config)) // TODO
	{
		close(fd);
		free_config(&config);
		return (ft_error("Error: Fallo al parsear el archivo.\n"));
	}
	if (!validate_config(&config)) // TODO
	{
		free_config(&config);
		return (ft_error("Error: Configuración inválida.\n"));
	}
	close(fd);
	// & Aquí el código para leer el archivo y parsear la configuración
	// & Programa del juego cub3d
	free_config(&config);
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