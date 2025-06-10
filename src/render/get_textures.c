/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-03 09:26:40 by madel-va          #+#    #+#             */
/*   Updated: 2025-06-03 09:26:40 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <stdio.h>


t_texture	load_texture(void  *mlx, char *path)
{
	t_texture	texture;

	printf("%s\n", path);
	if (access("./textures/greystone.xpm", F_OK) != 0)
	{
		perror("Error acceso a textura");
		printf("Ruta usada: %shhhh\n", "./textures/greystone.xpm");
		exit(EXIT_FAILURE);
	}
	texture.img = mlx_xpm_file_to_image(mlx, path, &texture.width, &texture.height);
	if (!texture.img)
		ft_error("Error cargando texturas\n");
	texture.pixels = (int *)mlx_get_data_addr(texture.img, &(int){0}, &(int){0}, &(int){0});
	return (texture);
}

