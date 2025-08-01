/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otro.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:00:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/01 05:41:08 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void   init_player_newversion(t_player *player)
{
    player->x = WIDTH / 2 - BLOCK / 4;
    player->y = HEIGHT / 2 - BLOCK / 4;
    player->angle = PI / 2;

    player->key_up = false;
    player->key_down = false;
    player->key_left = false;
    player->key_right = false;
    
    player->left_rotate = false;
    player->right_rotate = false;

    player->show_minimap = false;

}

int key_press_newversion(int keycode, t_player *player)
{
    if (keycode == KEY_W)
        player->key_up = true;
    if (keycode == KEY_S)
        player->key_down = true;
    if (keycode == KEY_A)
        player->key_left = true;
    if (keycode == KEY_D)
        player->key_right = true;
    if (keycode == KEY_LEFT)
        player->left_rotate = true;
    if (keycode == KEY_RIGHT)
        player->right_rotate = true;
    if (keycode == KEY_SPACE) // define KEY_M como desees, por ejemplo 46
        player->show_minimap = !player->show_minimap;


    return 0;
}

int key_release_newversion(int keycode, t_player *player)
{
    if (keycode == KEY_W)
        player->key_up = false;
    if (keycode == KEY_S)
        player->key_down = false;
    if (keycode == KEY_A)
        player->key_left = false;
    if (keycode == KEY_D)
        player->key_right = false;
    if (keycode == KEY_LEFT)
        player->left_rotate = false;
    if (keycode == KEY_RIGHT)
        player->right_rotate = false;
    return 0;
}





bool touch(float px, float py, t_game *game)
{
    int x = px / BLOCK;
    int y = py / BLOCK;

    // Validación de límites del mapa
    if (y < 0 || !game->config.map_lines[y])
        return true;

    if (x < 0 || x >= (int)ft_strlen(game->config.map_lines[y]))
        return true;

    return (game->config.map_lines[y][x] == '1');
}












































































/* void    move_player(t_player *player)
{
    int speed;
    float angle_speed;
    float cos_angle;
    float sin_angle;

    float side_angle = player->angle + PI / 2;
    

    speed = 3;
    angle_speed = 0.05;
    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);
    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;    
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;
    
    if (player->key_up)
    {
        player->x += cos_angle * speed;
        player->y += sin_angle * speed;
    }
    if (player->key_down)
    {
        player->x -= cos_angle * speed;
        player->y -= sin_angle * speed;
    }
    if (player->key_left)
    {
        player->x -= cos(side_angle) * speed;
        player->y -= sin(side_angle) * speed;
    }
    if (player->key_right)
    {
        player->x += cos(side_angle) * speed;
        player->y += sin(side_angle) * speed;
    }

    
} */

void move_player(t_player *player, t_game *game)
{
    float speed = 3;
    float angle_speed = 0.05;

    // Rotación
    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;

    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    if (player->angle < 0)
        player->angle += 2 * PI;

    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);
    float side_angle = player->angle + PI / 2;

    float new_x, new_y;

    // Adelante (W)
    if (player->key_up)
    {
        new_x = player->x + cos_angle * speed;
        new_y = player->y + sin_angle * speed;
        if (!touch(new_x, player->y, game))
            player->x = new_x;
        if (!touch(player->x, new_y, game))
            player->y = new_y;
    }

    // Atrás (S)
    if (player->key_down)
    {
        new_x = player->x - cos_angle * speed;
        new_y = player->y - sin_angle * speed;
        if (!touch(new_x, player->y, game))
            player->x = new_x;
        if (!touch(player->x, new_y, game))
            player->y = new_y;
    }

    // Izquierda (A)
    if (player->key_left)
    {
        new_x = player->x - cos(side_angle) * speed;
        new_y = player->y - sin(side_angle) * speed;
        if (!touch(new_x, player->y, game))
            player->x = new_x;
        if (!touch(player->x, new_y, game))
            player->y = new_y;
    }

    // Derecha (D)
    if (player->key_right)
    {
        new_x = player->x + cos(side_angle) * speed;
        new_y = player->y + sin(side_angle) * speed;
        if (!touch(new_x, player->y, game))
            player->x = new_x;
        if (!touch(player->x, new_y, game))
            player->y = new_y;
    }
}













void   put_pixel_newversion(int x, int y, int color, t_game *game)
{
    int index;
    
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;

    index = y * game->img.size_line + x * game->img.bpp / 8;
    game->img.data[index] = color & 0xFF;
    game->img.data[index + 1] = (color >> 8) & 0xFF;
    game->img.data[index + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
    int i = 0;
    while (i < size)
    {
        put_pixel_newversion(x + i, y, color, game); // Top
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel_newversion(x + i, y + size - 1, color, game); // Bottom
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel_newversion(x, y + i, color, game); // Left
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel_newversion(x + size - 1, y + i, color, game); // Right
        i++;
    }
}






























































void draw_rectangle(int x, int y, int width, int height, int color, t_game *game)
{
    int j = 0;
    while (j < height)
    {
        int i = 0;
        while (i < width)
        {
            put_pixel_newversion(x + i, y + j, color, game);
            i++;
        }
        j++;
    }
}
void fill_square(int x, int y, int size, int color, t_game *game)
{
    int i = 0, j;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            put_pixel_newversion(x + i, y + j, color, game);
            j++;
        }
        i++;
    }
}


void draw_minimap_newversion(t_game *game)
{
    int x, y;
    char **map = game->config.map_lines;

    // Calcular ancho y alto del mapa en bloques
    int map_width = 0;
    int map_height = 0;
    while (map[map_height])
    {
        int len = ft_strlen(map[map_height]);
        if (len > map_width)
            map_width = len;
        map_height++;
    }

    // Calcular tamaño del minimapa en píxeles
    int minimap_pixel_width = map_width * MINI_BLOCK;
    int minimap_pixel_height = map_height * MINI_BLOCK;

    // Calcular desplazamiento para centrar el minimapa
    int offset_x = (WIDTH - minimap_pixel_width) / 2;
    int offset_y = (HEIGHT - minimap_pixel_height) / 2;

    // Pintar fondo semitransparente solo donde haya celdas válidas
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            char c = map[y][x];
            if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                fill_square(x * MINI_BLOCK + offset_x,
                            y * MINI_BLOCK + offset_y,
                            MINI_BLOCK, 0x444444, game);
                if (c == '1')
                    draw_square(x * MINI_BLOCK + offset_x,
                                y * MINI_BLOCK + offset_y,
                                MINI_BLOCK, 0x00FF00, game);
            }
            x++;
        }
        y++;
    }

    // Pintar jugador
    int px = game->player.x / BLOCK * MINI_BLOCK + offset_x - 2;
    int py = game->player.y / BLOCK * MINI_BLOCK + offset_y - 2;
    draw_square(px, py, MINI_PLAYER_SIZE, 0xFF0000, game);

    // Pintar rayos
    float fraction = PI / 3 / WIDTH;
    float angle = game->player.angle - PI / 6;
    int i = 0;
    while (i < WIDTH)
    {
        if (i % 10 == 0)
        {
            float ray_x = game->player.x;
            float ray_y = game->player.y;
            float cos_a = cos(angle);
            float sin_a = sin(angle);

            while (!touch(ray_x, ray_y, game))
            {
                int mini_x = ray_x / BLOCK * MINI_BLOCK + offset_x;
                int mini_y = ray_y / BLOCK * MINI_BLOCK + offset_y;
                put_pixel_newversion(mini_x, mini_y, 0xAAAAAA, game);
                ray_x += cos_a;
                ray_y += sin_a;
            }
        }
        angle += fraction;
        i++;
    }
}





















void init_player_from_map(t_player *player, char **map)
{
    int y = 0;
    while (map[y])
    {
        int x = 0;
        while (map[y][x])
        {
            char c = map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                player->x = (x + 0.5) * BLOCK;
                player->y = (y + 0.5) * BLOCK;

                if (c == 'N')
                    player->angle = 3 * PI / 2;
                else if (c == 'S')
                    player->angle = PI / 2;
                else if (c == 'E')
                    player->angle = 0;
                else if (c == 'W')
                    player->angle = PI;

                map[y][x] = '0';  // lo dejamos como suelo para colisiones
                return;
            }
            x++;
        }
        y++;
    }
}





char **get_map_newversion(void)
{
    char **map = malloc(sizeof(char *) * 12);
    if (!map)
        return (NULL);

    map[0] = "11111111111111";
    map[1] = "10000000000001";
    map[2] = "10000000000001";
    map[3] = "10000000000001";
    map[4] = "10000000000001";
    map[5] = "10000100000001";
    map[6] = "10000000100001";
    map[7] = "10001000000001";
    map[8] = "10000000000001";
    map[9] = "10000000000001";
    map[10] = "11111111111111";
    map[11] = NULL;

    return map;
}

void draw_map_newversion(t_game *game)
{
    char    **map = game->config.map_lines;
    int     color = 0x00FF00;
    int     x, y;

    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
            x++;
        }
        y++;
    }
}

















int	init_game_newversion(t_game *game, t_config *config)
{
	int map_width = 0;
	int map_height = 0;
	int tile_size = 6;

	game->config = *config;


	init_player_newversion(&game->player);  // para resetear flags
    init_player_from_map(&game->player, game->config.map_lines);

	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (0);
        
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (!game->win_ptr)
		return (0);

	game->img.img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	if (!game->img.img_ptr)
		return (0);

	game->img.data = mlx_get_data_addr(game->img.img_ptr,
		&game->img.bpp, &game->img.size_line, &game->img.endian);
	if (!game->img.data)
		return (0);

    game->config.north = load_texture(game->mlx_ptr, "./textures/greystone.xpm");
    game->config.south = load_texture(game->mlx_ptr, "./textures/purplestone.xpm");
    game->config.east =  load_texture(game->mlx_ptr, "./textures/redbrick.xpm");
    game->config.west =  load_texture(game->mlx_ptr, "./textures/wood.xpm");
        
    for (int i = 0; game->config.map_lines[i]; i++)
    {
        printf("Línea %d: [%s]\n", i, game->config.map_lines[i]);
    }

	// 🔍 Obtener dimensiones del mapa dinámicamente
	while (game->config.map_lines && game->config.map_lines[map_height])
    {
        if (game->config.map_lines[map_height])
        {
            int len = ft_strlen(game->config.map_lines[map_height]);
            if (len > map_width)
                map_width = len;
        }
        map_height++;
    }

	game->minimap.width = map_width * tile_size;
	game->minimap.height = map_height * tile_size;
	game->minimap.img_ptr = mlx_new_image(game->mlx_ptr,
		game->minimap.width, game->minimap.height);
	if (!game->minimap.img_ptr)
		return (0);

	game->minimap.data = mlx_get_data_addr(game->minimap.img_ptr,
		&game->minimap.bpp, &game->minimap.size_line, &game->minimap.endian);
	if (!game->minimap.data)
		return (0);

	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);

	return (1);
}



/* void init_game_newversion(t_game *game)
{
    init_player_newversion(&game->player);
    game->config.map_lines = get_map_newversion();
    game->mlx_ptr = mlx_init();
    game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "GAME");
    game->img.img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
    game->img.data = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.size_line, &game->img.endian);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
} */


void clear_image_newversion(t_game *game)
{
    int x, y;
    int ceiling_color = 0x87CEEB; // Azul cielo
    int floor_color = 0x323232;   // Gris oscuro

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            if (y < HEIGHT / 2)
                put_pixel_newversion(x, y, ceiling_color, game);
            else
                put_pixel_newversion(x, y, floor_color, game);
            x++;
        }
        y++;
    }
}

















float distance(float x, float y)
{
    return sqrt(x * x + y * y);
}

float real_distance(float ray_x, float ray_y, t_game *game)
{
    float delta_x = ray_x - game->player.x;
    float delta_y = ray_y - game->player.y;
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float real_dist = distance(delta_x, delta_y) * cos(angle);
    
    return real_dist;
}


void draw_lines_newversion(t_player *player, t_game *game, float angle, int x_column)
{
	float ray_x = player->x;
	float ray_y = player->y;
	float cos_a = cos(angle);
	float sin_a = sin(angle);

	while (!touch(ray_x, ray_y, game))
	{
		ray_x += cos_a;
		ray_y += sin_a;
	}

	float delta_x = ray_x - player->x;
	float delta_y = ray_y - player->y;
	float dist = sqrt(delta_x * delta_x + delta_y * delta_y);
	float corrected_dist = dist * cos(angle - player->angle);

	int line_height = (BLOCK / corrected_dist) * (WIDTH / 2);
	int draw_start = (HEIGHT - line_height) / 2;
	if (draw_start < 0) draw_start = 0;
	int draw_end = draw_start + line_height;
	if (draw_end > HEIGHT) draw_end = HEIGHT;

	t_texture *tex = &game->config.north;

	// Coordenada en textura (usamos ray_y para verticales, o ray_x para horizontales si prefieres)
	float wall_hit = fmod(ray_y, BLOCK); // puedes usar ray_x también
	int tex_x = (wall_hit / BLOCK) * tex->width;
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= tex->width) tex_x = tex->width - 1;

	int y = draw_start;
	while (y < draw_end)
	{
		int d = y * 256 - HEIGHT * 128 + line_height * 128;
		int tex_y = (d * tex->height) / (line_height * 256);
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= tex->height) tex_y = tex->height - 1;

		int color = tex->pixels[tex_y * tex->width + tex_x];
		put_pixel_newversion(x_column, y, color, game);
		y++;
	}
}






int draw_loop_newversion(t_game *game)
{
    t_player *player;

    player = &game->player;
    move_player(player, game);
    clear_image_newversion(game);

    float fraction = PI / 3 / WIDTH;
    float start_x = player->angle - PI / 6;
    int i = 0;
    while (i < WIDTH)
    {
        draw_lines_newversion(player, game, start_x, i);
        start_x += fraction;
        i++;
    }
        
        
    if (player->show_minimap)
        draw_minimap_newversion(game);

    
    
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);

    return 0;
}










/* int	main()
{
	
    t_game game;

    init_game_newversion(&game);

    mlx_hook(game.win_ptr, 2, 1L<<0, key_press_newversion, &game.player);
    mlx_hook(game.win_ptr, 3, 1L<<1, key_release_newversion, &game.player);

    
    mlx_loop_hook(game.mlx_ptr, draw_loop_newversion, &game);
    mlx_loop(game.mlx_ptr);

	return (0);
} */