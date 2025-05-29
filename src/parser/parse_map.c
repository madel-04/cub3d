/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:47:52 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/28 22:47:52 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_tabtospaces(char *str)
{
	char	*res;
	int		i = 0, j = 0, len = 0, tabs = 0;

	
	if (!str)
		return (NULL);
	if (str[0] == '\0')
		return (free(str), ft_strdup(""));  // o malloc(1) + '\0'
	while (str[len])
	{
		if (str[len] == '\t')
			tabs++;
		len++;
	}
	res = malloc(len + tabs * 3 + 1);
	if (!res)
		return (free(str), NULL);
	while (str[i])
	{
		if (str[i] == '\t')
		{
			res[j++] = ' ';
			res[j++] = ' ';
			res[j++] = ' ';
			res[j++] = ' ';
		}
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	free(str);
	return (res);
}


int	ft_parse_map(int fd, t_config *config, char *first_line)
{
	char	**map;
	char	*line;
	int		lines_alloc;
	int		lines_count;
	int		ret;

	lines_alloc = 32;
	lines_count = 0;
	map = malloc(sizeof(char *) * (lines_alloc + 1));
	if (!map)
		return (0);
	map[lines_count++] = ft_strdup(first_line);
	if (!map[0])
		return (free(map), 0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		line = ft_tabtospaces(line);
		if (!ft_is_map_line(line))
		{
			free(line);
			break;
		}
		if (lines_count >= lines_alloc)
		{
			lines_alloc *= 2;
			char **tmp = ft_realloc_strarray(map, lines_count, lines_alloc); //TODO
			if (!tmp)
				return (free_strarray(map), 0); // TODO
			map = tmp;
		}
		map[lines_count++] = line;
		//printf("%s\n", line); // Debug
	}
	map[lines_count] = NULL;
	config->map_lines = map; // !Guardar el puntero al mapa en config->map_lines
	return (1);
}

//! Comprobar que solo haya un jugador
//

/*
get_next_line debe liberar correctamente la línea en caso de error.
Qué pasa si ret == -1 (error de lectura)? detectar ese caso y liberar todo.

*/
