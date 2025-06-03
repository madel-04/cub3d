/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:55:23 by madel-va          #+#    #+#             */
/*   Updated: 2025/06/02 13:43:50 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h> 
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
	int		*pixels;
}	t_texture;

typedef struct	s_config
{
	int			res_x;
	int			res_y;                   // <- R línea
	char			*textures[4];            // [NO, SO, WE, EA]  <- líneas de textura 
	int			floor_color[3];          // <- F línea
	int			ceiling_color[3];        // <- C línea
	char		**map_lines;            // <- Lista de líneas del mapa
	char		*textures_path[4];
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}	t_config;

typedef struct s_img
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed; // Velocidad de movimiento
	double	rot_speed;  // Velocidad de rotación
}		t_player;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		textures[4]; // NO, SO, WE, EA
	t_img		img; // imagen del frame actual
	t_config	config;
	t_player	player;
	int			win_width;
	int			win_height;
}			t_game;


// *** CONFIG INIT ***
void		ft_config_init(t_config *config);
int			init_game(t_game *game, t_config *config);
int			ft_init_player(t_game *game, char **map_lines);

// *** RENDER ***
int			get_rgb(int color[3]);
void		put_pixel(t_img *img, int x, int y, int color);
void		draw_background(t_game *game);
int			render_frame(t_game *game);
t_texture	load_texture(void  *mlx, char *path);

// *** PARSEO ***
int 		ft_parse_config(int fd, t_config *config);
int			ft_parse_texture(char *line, t_config *config, int index);
int			ft_parse_color(char *line, int *color_array);
int			ft_parse_map(int fd, t_config *config, char *first_line);
int			ft_is_map_line(const char *line);


// *** VALIDATIONS ***
int			validate_config(t_config *config, t_game *game);
int			has_valid_textures(char **textures, t_config *config, t_game *game);
int			has_valid_player(char **map);
void		free_map(char **map);
int			flood_fill(char **map, int x, int y);
int			find_player_start(char **map, int *x, int *y);
char 		**copy_map(char **map);
int			is_map_closed(char **map);

// *** FREE ***
void free_config(t_config *config);

// *** UTILS ***
int			ft_error(const char *message);
char		**ft_realloc_strarray(char **old, int old_count, int new_alloc);
void		free_strarray(char **arr);
void		ft_strarray_free(char **arr);
int			ft_strarray_len(char **arr);
int			ft_isspace(int c);
char		*ft_tabtospaces(char *str);

#endif
