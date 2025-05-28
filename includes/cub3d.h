/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 09:55:23 by madel-va          #+#    #+#             */
/*   Updated: 2025-05-28 09:55:23 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "minilibx-linux/mlx.h"
// TODO # include "get_next_line.h"
# include <math.h>
# include <fcntl.h> 
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct	s_config {
	int		res_x;
	int		res_y;                   // <- R línea
	char	*textures[4];            // [NO, SO, WE, EA]  <- líneas de textura 
	int		floor_color[3];          // <- F línea
	int		ceiling_color[3];        // <- C línea
	char	**map_lines;            // <- Lista de líneas del mapa
}	t_config;

// *** CONFIG INIT ***
void ft_config_init(t_config *config);

// *** PARSEO ***
int ft_parse_config(int fd, t_config *config);

// *** FREE ***
void free_config(t_config *config);

#endif