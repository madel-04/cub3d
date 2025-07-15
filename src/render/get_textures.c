/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:26:40 by madel-va          #+#    #+#             */
/*   Updated: 2025/06/11 13:46:16 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void print_first_diff(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] && s2[i]) {
        if (s1[i] != s2[i]) {
            printf("Diferencia en la posición %d: '%c' vs '%c'\n", i, s1[i], s2[i]);
            return;
        }
        i++;
    }
	if (s1[i] || s2[i]) {
		printf("Diferente longitud en la posición %d: '%c' (%d) vs '%c' (%d)\n", i, s1[i], s1[i], s2[i], s2[i]);
	} else {
		printf("Las cadenas son iguales\n");
	}
}*/

t_texture	load_texture(void *mlx, char *path)
{
	t_texture	texture;

	(void)mlx;
//	printf("%s\n", path);
//	print_first_diff(path, "./textures/greystone.xpm");
//	if (strcmp(path, "./textures/greystone.xpm") != 0)
//		printf("no son iguales \n");
	if (access("./textures/greystone.xpm", F_OK) != 0)
	{
		perror("Error acceso a textura");
	//	printf("Ruta usada: %s\n", "./textures/greystone.xpm");
		exit(EXIT_FAILURE);
	}
	texture.img = mlx_xpm_file_to_image(mlx, path, &texture.width,
			&texture.height);
	if (!texture.img)
		ft_error("Error cargando texturas\n");
	texture.pixels = (int *)mlx_get_data_addr(texture.img, &(int){0},
			&(int){0}, &(int){0});
	return (texture);
}
