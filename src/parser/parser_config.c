/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:53:38 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/28 22:47:37 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_strtrim_inplace(char *line)
{
	char	*start;
	char	*end;

	start = line;
	while (ft_isspace(*start)) // elimina espacios o tabs al inicio
		start++;
	end = line + ft_strlen(line) - 1;
	while (end > start && ft_isspace(*end)) // elimina al final
		*end-- = '\0';
	if (start != line)
		ft_memmove(line, start, end - start + 2); // mueve la parte limpia al principio
}

static int ft_is_map_line(const char *line)
{
	while (*line)
	{
		if (!ft_strchr(" 012NSEW", *line))
			return (0);
		line++;
	}
	return (1);
}
static int ft_parse_element(char *line, t_config *config)
{
	if (ft_strncmp(line, "R ", 2) == 0)
		return (ft_parse_resolution(line + 1, config));
	else if (ft_strncmp(line, "NO ", 3) == 0)
		return (ft_parse_texture(line + 2, config, 0)); 
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (ft_parse_texture(line + 2, config, 1));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (ft_parse_texture(line + 2, config, 2));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (ft_parse_texture(line + 2, config, 3));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (ft_parse_color(line + 1, config->floor_color));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (ft_parse_color(line + 1, config->ceiling_color));
	return (0); // línea no reconocida
}

int ft_parse_config(int fd, t_config *config)
{
	char	*line;
	int		ret;

	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_strtrim_inplace(line); // TODO debería eliminar espacios al principio y al final
		if (line[0] == '\0') // línea vacía
		{
			free(line);
			continue;
		}
		if (ft_is_map_line(line)) // línea de mapa (empieza con 0,1,N,...)
		{
			if (!ft_parse_map(fd, config, line)) // TODO pasa línea actual + resto
				return (free(line), 0);
			return (1); // mapa se parsea hasta el final, termina aquí
		}
		if (!ft_parse_element(line, config)) // cabeceras R, NO, F, C...
			return (free(line), 0);
		free(line);
	}
	if (ret < 0)
		return (0); // error de lectura
	return (0);
}
// !He leido que está bien que se transformen las tabulaciones en 4 espacios, no sé si tamb se aplica en el mapa
