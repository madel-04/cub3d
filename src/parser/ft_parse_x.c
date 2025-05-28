/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:49:58 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/28 22:49:58 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_parse_texture(char *line, t_config *config, int index)
{
	while (*line == ' ') line++; // Saltar espacios iniciales
	if (config->textures[index] != NULL)
		return (ft_error("Textura duplicada.\n"));
	config->textures[index] = ft_strdup(line);
	if (!config->textures[index])
		return (ft_error("Fallo de memoria al guardar textura.\n"));
	return (1);
}

int	ft_parse_color(char *line, int *color_array)
{
	char	**components;
	int		i;
	int		value;

	while (*line == ' ') line++; // saltar espacios
	components = ft_split(line, ',');
	if (!components || ft_strarray_len(components) != 3)
		return (ft_error("Color debe tener 3 componentes.\n"));
	for (i = 0; i < 3; i++)
	{
		value = ft_atoi(components[i]);
		if (value < 0 || value > 255)
		{
			ft_strarray_free(components);
			return (ft_error("Color fuera de rango (0-255).\n"));
		}
		color_array[i] = value;
	}
	ft_strarray_free(components);
	return (1);
}
