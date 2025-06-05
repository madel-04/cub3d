#include "./minilib/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <fcntl.h>
# include <stdint.h>
# include <limits.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720
#define MAP_WIDTH 24
#define MAP_HEIGHT 24


/* ================ SETTINGS KEYS ================ */
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_UP 65362
#define KEY_RIGHT 65363
#define KEY_DOWN 65364
#define ON_DESTROY 17


typedef struct s_game
{
	void			*mlx;
	void			*win;
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
    int     color; 
}					t_game;



int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


void	*ft_memset(void *str, int value, size_t len)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)str;
	while (len > i)
	{
		s[i] = (unsigned char)value;
		i++;
	}
	return (s);
}

void	ft_bzero(void *str, size_t len)
{
	ft_memset(str, '\0', len);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (count == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	str = malloc(count * size);
	if (!str)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}

// Dibuja una línea vertical
void draw_vertical_line(t_game *game, int x, int drawStart, int drawEnd, int color)
{
    int y;
    for (y = drawStart; y < drawEnd; y++)
        mlx_pixel_put(game->mlx, game->win, x, y, color);
}

// Dibuja la escena (raycasting)
void draw_scene(t_game *game)
{
    int x;
    for (x = 0; x < SCREEN_WIDTH; x++)
    {
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double rayDirX = game->dirX + game->planeX * cameraX;
        double rayDirY = game->dirY + game->planeY * cameraX;
        int mapX = (int)(game->posX);
        int mapY = (int)(game->posY);

        double sideDistX, sideDistY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;
        int stepX, stepY, hit = 0, side;

        if (rayDirX < 0) { stepX = -1; sideDistX = (game->posX - mapX) * deltaDistX; }
        else { stepX = 1; sideDistX = (mapX + 1.0 - game->posX) * deltaDistX; }
        if (rayDirY < 0) { stepY = -1; sideDistY = (game->posY - mapY) * deltaDistY; }
        else { stepY = 1; sideDistY = (mapY + 1.0 - game->posY) * deltaDistY; }

        while (hit == 0)
        {
            if (sideDistX < sideDistY) { sideDistX += deltaDistX; mapX += stepX; side = 0; }
            else { sideDistY += deltaDistY; mapY += stepY; side = 1; }
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }
        if (side == 0) perpWallDist = (mapX - game->posX + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - game->posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

        int color;
        switch (worldMap[mapX][mapY]) {
            case 1:  color = 0xFF0000; break;
            case 2:  color = 0x00FF00; break;
            case 3:  color = 0x0000FF; break;
            default: color = 0xAAAAAA; break;
        }
        if (side == 1) color /= 2;

        color = game->color; // <--- siempre el color global
        draw_vertical_line(game, x, drawStart, drawEnd, color);
    }
}

int	handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
    {
		mlx_destroy_window(game->mlx, game->win);
		exit(EXIT_SUCCESS);
	}
    if (keycode == KEY_W || keycode == KEY_UP)
    {
        printf("W");
        game->color = 0xFF0000;
    }
    if (keycode == KEY_S || keycode == KEY_DOWN)
    {
        printf("S");
        game->color = 0x0000FF;
    }
    if (keycode == KEY_A || keycode == KEY_LEFT)
    {
        printf("A");
        game->color = 0xFFFF00;
    }
    if (keycode == KEY_D || keycode == KEY_RIGHT)
    {
        printf("D");
        game->color = 0x00FF00;
    }
    mlx_clear_window(game->mlx, game->win);
    draw_scene(game);
	return (0);
}

int	handle_cross(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (ac == 0)
        printf("MAL");
	else
	{
		game->mlx = mlx_init();
        game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
        
        mlx_hook(game->win, ON_DESTROY, 0, handle_cross, game);
        mlx_key_hook(game->win, handle_key, game);


        game->posX = 22.0; game->posY = 12.0;
        game->dirX = -1.0; game->dirY = 0.0;
        game->planeX = 0.0; game->planeY = 0.66;

        game->color = 0x0000FF; // color inicial

        draw_scene(game);

        mlx_loop(game->mlx);
	}
	return (0);
}