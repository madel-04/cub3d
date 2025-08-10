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

/*int	ft_parse_map(int fd, t_config *config, char *first_line)
{
	char	**map;
	char	*line;
	int		lines_alloc;
	int		lines_count;
	int		ret;
	char	*temp;

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
	config->map_lines = map;
	return (1);
}*/
static int	ft_add_map_line(char *line, char ***map,
	t_config *config, int *lines_count)
{
	char	**tmp;
	int		lines_alloc;

	(void)config;
	lines_alloc = 32;
	while (*lines_count >= lines_alloc)
		lines_alloc *= 2;
	tmp = ft_realloc_strarray(*map, *lines_count, lines_alloc);
	if (!tmp)
	{
		free_strarray(*map);
		return (0);
	}
	*map = tmp;
	(*map)[(*lines_count)++] = line;
	return (1);
}

static int	ft_read_map_lines(int fd, char ***map, int *lines_count)
{
	char	*line;
	char	*temp;
	int		i;

	i = get_next_line(fd, &line);
	while (i >= 0)
	{
		temp = line;
		line = ft_tabtospaces(temp);
		free(temp);
		if (!line)
			return (free_strarray(*map), 0);
		if (!ft_is_map_line(line) && !ft_isspace(*line) && *line != '\0')
		{
			free(line);
			ft_error("No puede haber configuraciones después del mapa\n");
		}
		if (!ft_add_map_line(line, map, NULL, lines_count))
			return (0);
		if (i == 0)
			break ;
		i = get_next_line(fd, &line);
	}
	return (1);
}

int	ft_parse_map(int fd, t_config *config, char *first_line)
{
	char	**map;
	int		lines_count;

	lines_count = 0;
	map = malloc(sizeof(char *) * 33);
	if (!map)
		return (0);
	map[lines_count++] = ft_strdup(first_line);
	if (!map[0])
		return (free(map), 0);
	if (!ft_read_map_lines(fd, &map, &lines_count))
		return (0);
	map[lines_count] = NULL;
	config->map_lines = map;
	return (1);
}

/*
get_next_line debe liberar correctamente la línea en caso de error.
Qué pasa si ret == -1 (error de lectura)? detectar ese caso y liberar todo.
*/

static int	ft_is_map_line_trailing(const char *line)
{
	const char	*temp;

	if (ft_isspace(*line))
	{
		temp = line;
		while (*temp && ft_isspace(*temp))
			temp++;
		if (*temp != '\0')
			return (0);
	}
	return (1);
}

int	ft_is_map_line(const char *line)
{
	int			has_map_char;

	has_map_char = 0;
	while (*line && ft_isspace(*line))
		line++;
	while (*line)
	{
		if (*line == '0' || *line == '1'
			|| *line == 'N' || *line == 'S'
			|| *line == 'E' || *line == 'W'
			|| *line == ' ')
			has_map_char = 1;
		else if (ft_isspace(*line))
		{
			if (!ft_is_map_line_trailing(line))
				return (0);
			break ;
		}
		else
			return (0);
		line++;
	}
	return (has_map_char);
}
