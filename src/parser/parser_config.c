/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:53:38 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/10 18:33:46 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_parse_element(char *line, t_config *config)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0')
		return (1);
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
	return (0);
}

static int	ft_handle_config_line(char *line, int fd, t_config *config)
{
	char	*temp;

	temp = line;
	line = ft_tabtospaces(line);
	free(temp);
	if (!line)
		return (0);
	if (line[0] == '\0' || ft_is_line_blank(line))
		return (free(line), 1);
	if (ft_is_map_line(line))
	{
		if (!ft_parse_map(fd, config, line))
		{
			printf("Error parsing map line: %s\n", line);
			return (free(line), 0);
		}
		free(line);
		return (2);
	}
	if (!ft_parse_element(line, config))
		printf("Error parsing element: %s\n", line);
	return (free(line), 1);
}

static int	handle_line_before_map(char *line, int fd, t_config *config,
		int *map_found)
{
	int	status;

	status = ft_handle_config_line(line, fd, config);
	if (status == 0)
		return (0);
	if (status == 2)
		*map_found = 1;
	return (1);
}

static int	validate_line_after_map(char *line)
{
	if (line[0] != '\0' && !ft_is_line_blank(line))
	{
		free(line);
		ft_error("Error: Hay líneas después del mapa.\n");
		return (0);
	}
	free(line);
	return (1);
}

int	ft_parse_config(int fd, t_config *config)
{
	char	*line;
	int		ret;
	int		map_found;

	line = NULL;
	map_found = 0;
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		if (!map_found)
		{
			if (!handle_line_before_map(line, fd, config, &map_found))
				return (0);
		}
		else if (!validate_line_after_map(line))
			return (0);
		ret = get_next_line(fd, &line);
	}
	free(line);
	if (ret < 0)
		return (0);
	return (map_found);
}
// !He leido que está bien que se transformen las tabulaciones en 4 espacios,
//	no sé si tamb se aplica en el mapa
