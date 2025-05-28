
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
/*
+---------------------+
|   Leer línea (GNL)  |
+---------------------+
		  |
		  v
+-----------------------------+
| ¿Es línea vacía o espacio? |
+-----------------------------+
		  |
	+-----+-----+
	|           |
   Sí          No
	|           |
	v           v
[Ignorar]   +-----------------------------+
			| ¿Contiene solo caracteres   |
			| válidos de mapa?           |
			| [0,1,2,N,S,E,W, espacio]    |
			+-----------------------------+
						|
				 +------+------+
				 |             |
				Sí            No
				 |             |
				 v             v
	  +-------------------+  +---------------------------+
	  | Agregar a lista   |  | ¿Es cabecera (R, NO, SO)? |
	  | de líneas de mapa |  +---------------------------+
	  +-------------------+             |
									   +---> Sí: Parsear y guardar
									   |
									   +---> No: Error o ignorar


+------------------------------+
|  ¿Hay exactamente 1 jugador? |
+------------------------------+
		   |
	 +-----+------+
	 |            |
	Sí           No
	 |            |
	 v            v
[Continuar]   [Error: múltiples jugadores]

+-----------------------------+
| ¿El mapa está cerrado?     |
| (Flood fill o bordes)      |
+-----------------------------+
		   |
	 +-----+------+
	 |            |
	Sí           No
	 |            |
	 v            v
[Correcto]    [Error: mapa abierto]
+-----------------------------+ */

#include "cub3d.h"

void ft_config_init(t_config *config)
{
	int i;

	i = 0;
	config->res_x = 0;
	config->res_y = 0;
	while (i < 4)
		config->textures[i++] = NULL; // Inicializar las texturas a NULL
	i = 0;
	while (i < 3)
	{
		config->floor_color[i] = -1; // Inicializar colores a -1
		config->ceiling_color[i] = -1;
		i++;
	}
	config->map_lines = NULL; // Inicializar como NULL o una lista vacía
}

int main(int argc, char **argv)
{
	t_config config;
	int fd;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Número incorrecto de argumentos.\n", 2); // TODO
		return (1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error: El archivo debe tener extensión .cub\n", 2); // TODO
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: No se pudo abrir el archivo.\n", 2); // TODO
		return (1);
	}
	ft_config_init(&config); // & Inicializar la configuración
	if (!ft_parse_config(fd, &config)) // TODO
	{
		close(fd);
		free_config(&config); //TODO
		return (ft_error("Error: Fallo al parsear el archivo.\n"));
	}
	if (!validate_config(&config)) // TODO
	{
		free_config(&config);
		return (ft_error("Error: Configuración inválida.\n"));
	}
	// & Aquí el código para leer el archivo y parsear la configuración
	// & Programa del juego cub3d
	close(fd);
	free_config(&config); //TODO 
	return (0);
}
