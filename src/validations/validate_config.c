/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:48:48 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/28 22:48:48 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_config(t_config *config)
{
	if (!config->textures[0] || !config->textures[1] ||
		!config->textures[2] || !config->textures[3])
		return (ft_error("Faltan texturas.\n"));
	if (config->floor_color[0] == -1 || config->ceiling_color[0] == -1)
		return (ft_error("Colores de suelo o techo inválidos.\n"));
	if (!is_map_closed(config->map_lines))
		return (ft_error("El mapa no está cerrado por muros.\n"));
	if (!has_valid_player(config->map_lines))
		return (ft_error("Jugador no válido o ausente.\n"));
	return (1);
}
