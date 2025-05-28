/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 10:50:36 by madel-va          #+#    #+#             */
/*   Updated: 2025-05-28 10:50:36 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
