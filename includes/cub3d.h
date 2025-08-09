/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:55:23 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/09 20:40:11 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

// ==== LIBRERÍAS ====
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

// ==== DEFINICIONES ====
# define WIDTH				1280
# define HEIGHT			720
# define BLOCK			64

# define MINI_BLOCK		16
# define MINI_PLAYER_SIZE	4
# define MINI_MAP_OFFSET_X	10
# define MINI_MAP_OFFSET_Y	10
# define PI				3.14159265359

# define KEY_ESC		65307
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define KEY_SPACE		32

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
	char		*textures[4];            // [NO, SO, WE, EA]  <- líneas de textura 
	int			floor_color[3];          // <- F línea
	int			ceiling_color[3];        // <- C línea
	char		**map_lines;            // <- Lista de líneas del mapa
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
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
	bool	show_minimap;
}		t_player;

typedef struct s_draw_data
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	size;
	int	color;
	int	offset_x;
	int	offset_y;
}	t_draw_data;

typedef struct s_spawn_info
{
	int		x;
	int		y;
	char	c;
}	t_spawn_info;

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

	t_img		minimap;
	t_draw_data	draw;
}			t_game;


// *** CONFIG INIT ***
void		ft_config_init(t_config *config);
int			init_game(t_game *game, t_config *config);
int			ft_init_player(t_game *game, char **map_lines);
void		set_orientation_north(t_game *game);
void		set_orientation_south(t_game *game);
void		set_orientation_east(t_game *game);
void		set_orientation_west(t_game *game);

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
void 		free_config(t_config *config);
void		free_game(t_game *game);

// *** UTILS ***
int			ft_error(const char *message);
char		**ft_realloc_strarray(char **old, int old_count, int new_alloc);
void		free_strarray(char **arr);
void		ft_strarray_free(char **arr);
int			ft_strarray_len(char **arr);
int			ft_isspace(int c);
char		*ft_tabtospaces(char *str);
char		*ft_strdup_textures(const char *s);
int			ft_is_line_blank(const char *line);
int			ft_atoi_2(const char *str);


// *** KEYS ***
int			handle_key(int keycode, t_game *game);
int			handle_key_release(int keycode, t_game *game);





int			key_press_newversion(int keycode, t_player *player);
int			key_release_newversion(int keycode, t_player *player);


// *** RAYCASTING ***
// DRAW MINIMAP UTILS
void		draw_rectangle(int x, int y, int width, int height, int color, t_game *game);
void		fill_square(int x, int y, int size, int color, t_game *game);
void		draw_background_cell(char c, int x, int y, t_game *game, int offset_x, int offset_y);
void		draw_map_background(t_game *game, int offset_x, int offset_y);
void		draw_single_ray(float angle, t_game *game, int offset_x, int offset_y);

// DRAW MINIMAP
void		draw_minimap_rays(t_game	*game, int offset_x, int offset_y);
void		draw_minimap_mini(t_game *game, int offset_x, int offset_y);
void		draw_minimap_newversion(t_game *game);

// MOVE PLAYER
void		move_forward(t_player *player, t_game *game, float angle, float speed);
void		move_backward(t_player *player, t_game *game, float angle, float speed);
void		move_left(t_player *player, t_game *game, float side_a, float speed);
void		move_right(t_player *player, t_game *game, float side_a, float speed);
void		move_player(t_player *player, t_game *game);

// RAYCASTING INITS UTILS
void		set_player_angle(t_player *player, char **map, t_spawn_info info);
void		rotate_player(t_player *player, float angle_speed);
int			charge_textures(t_game *game);
void		get_map_dimensions(t_game *game, int *map_width, int *map_height);

// RAYCASTING INITS
void		init_player_from_map(t_player *player, char **map);
int			init_window_and_images(t_game *game);
int			init_minimap(t_game *game, int map_width, int map_height, int tile_size);
void		init_player_newversion(t_player *player);
int			init_game_newversion(t_game *game, t_config *config);

// RAYCASTING UTILS
int			rgb_to_int(int r, int g, int b);
float		distance(float x, float y);
bool		touch(float px, float py, t_game *game);
void		put_pixel_newversion(int x, int y, int color, t_game *game);
void		draw_square(int x, int y, int size, int color, t_game *game);

// RAYCASTING
float		real_distance(float ray_x, float ray_y, t_game *game);
void		clear_image_newversion(t_game *game);
void		draw_lines_newversion(t_player *player, t_game *game, float ray_angle, int column);
int			draw_loop_newversion(t_game *game);


// OTRO



#endif
