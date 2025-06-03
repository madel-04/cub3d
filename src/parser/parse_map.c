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

/*
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
		return (NULL);
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
*/
#include <stdlib.h>
#include <string.h>

char *ft_tabtospaces(char *str)
{
	size_t len;
	size_t i;
	size_t j;
	char *new_str;
	int		k;

    if (!str)
		return NULL;
    len = strlen(str);
	k = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '\t')
			k++;
		i++;
	}
    new_str = malloc(len + (k * 3) + 1);
    if (!new_str)
		return NULL;
    i = 0;
	j = 0;
    while (str[i])
	{
        if (str[i] == '\t')
		{
            new_str[j++] = ' ';
            new_str[j++] = ' ';
            new_str[j++] = ' ';
            new_str[j++] = ' ';
		}
		else
            new_str[j++] = str[i];
        i++;
    }
    new_str[j] = '\0';
    return new_str;
}


int	ft_parse_map(int fd, t_config *config, char *first_line)
{
	char	**map;
	char	*line;
	int		lines_alloc;
	int		lines_count;
	int		ret;
	char	*temp;

	printf("Parsing map...\n");
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
		temp = line;
		line = ft_tabtospaces(line);
		free(temp);
		if (!line)
		{
			free_strarray(map);
			return (0);
		}
		printf("Read line: %s\n", line);
		if (!ft_is_map_line(line))
		{
			free(line); // &PRIMERA
			break;
		}
		if (lines_count >= lines_alloc)
		{
			lines_alloc *= 2;
			char **tmp = ft_realloc_strarray(map, lines_count, lines_alloc);
			if (!tmp)
				return (free_strarray(map), 0);
			map = tmp;
		}
		map[lines_count++] = line;
	}
	if (ret == 0 && line)
		free(line);
	map[lines_count] = NULL;
	config->map_lines = map; // !Guardar el puntero al mapa en config->map_lines
	return (1);
}

/*
get_next_line debe liberar correctamente la línea en caso de error.
Qué pasa si ret == -1 (error de lectura)? detectar ese caso y liberar todo.
*/
