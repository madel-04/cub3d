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

int	ft_parse_texture(char *line, t_config *config, int i)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (config->textures[i] != NULL)
		return (ft_error("Textura duplicada.\n"));
	config->textures[i] = ft_strdup_textures(line);
	if (!config->textures[i])
		return (ft_error("Fallo de memoria al guardar textura.\n"));
	return (1);
}

static int	is_color_set(int *color_array)
{
	if (color_array[0] != -1 || color_array[1] != -1 || color_array[2] != -1)
		return (1);
	return (0);
}

static int	validate_and_parse_components(char **components, int *color_array)
{
	int	i;
	int	value;

	i = 0;
	while (i < 3)
	{
		value = ft_atoi_2(components[i]);
		if (value < 0 || value > 255)
			return (ft_error("Color fuera de rango (0-255).\n"));
		color_array[i] = value;
		i++;
	}
	return (1);
}

int	ft_parse_color(char *line, int *color_array)
{
	char	**components;

	if (is_color_set(color_array))
		return (ft_error("Error: los colores ya han sido declarados\n"));
	while (*line == ' ' || *line == '\t')
		line++;
	components = ft_split(line, ',');
	if (!components || ft_strarray_len(components) != 3)
	{
		if (components)
			ft_strarray_free(components);
		return (ft_error("Color debe tener 3 componentes.\n"));
	}
	if (!validate_and_parse_components(components, color_array))
	{
		ft_strarray_free(components);
		return (0);
	}
	ft_strarray_free(components);
	return (1);
}
