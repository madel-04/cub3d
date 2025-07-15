/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:53:38 by madel-va          #+#    #+#             */
/*   Updated: 2025/06/12 14:10:47 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	{
		printf("Empty line detected, skipping.\n");
		free(line);
		return (1);
	}
	if (ft_is_map_line(line))
	{
		if (!ft_parse_map(fd, config, line))
		{
			printf("Error parsing map line: %s\n", line);
			free(line);
			return (0);
		}
		free(line);
		return (2);
	}
	if (!ft_parse_element(line, config))
		printf("Error parsing element: %s\n", line);
	return (free(line), 1);
}

int	ft_parse_config(int fd, t_config *config)
{
	char	*line;
	int		ret;
	int		status;
	int		map_found;

	line = NULL;
	map_found = 0;
	printf("Parsing configuration...\n");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("Read line: %s\n", line);
		if (!map_found)
		{
			status = ft_handle_config_line(line, fd, config);
			if (status == 0)
				return (0);
			if (status == 2)
				map_found = 1;
		}
		else
		{
			if (line[0] != '\0' && !ft_is_line_blank(line))
			{
				free(line);
				ft_error("Error: Hay líneas después del mapa.\n");
				return (0);
			}
			free(line);
		}
	}
	free(line);
	printf("Finished parsing configuration.\n");
	if (ret < 0)
		return (0);
	return (map_found);
}

/*int	ft_parse_config(int fd, t_config *config)
{
	char	*line;
	int		ret;
	char	*temp;

	line = NULL;
	printf("Parsing configuration...\n");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("Read line: %s\n", line);
		temp = line;
		line = ft_tabtospaces(line);
		free(temp);
		if (line[0] == '\0' || ft_is_line_blank(line)) // línea vacía
		{
			printf("Empty line detected, skipping.\n");
			free(line);
			continue;
		}
		if (ft_is_map_line(line)) // línea de mapa (empieza con 0,1,N,...)
		{
			if (!ft_parse_map(fd, config, line))
			{
				printf("Error parsing map line: %s\n", line);
				return (free(line), 0);
			}
			free(line);
			return (1); // mapa se parsea hasta el final, termina aquí
		}
		if (!ft_parse_element(line, config)) // cabeceras R, NO, F, C...
			printf("Error parsing element: %s\n", line);
		free(line);
	}
	printf("Finished parsing configuration.\n");
	if (ret < 0)
		return (0);
	return (0);
}*/
// !He leido que está bien que se transformen las tabulaciones en 4 espacios, no sé si tamb se aplica en el mapa
