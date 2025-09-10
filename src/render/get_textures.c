/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:26:40 by madel-va          #+#    #+#             */
/*   Updated: 2025/08/08 07:03:34 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	load_texture(void *mlx, char *path)
{
	t_texture	texture;

    texture.img = mlx_xpm_file_to_image(mlx, path, &texture.width,
	    &texture.height);
    if (!texture.img)
	ft_error("Error cargando texturas\n");
    texture.pixels = (int *)mlx_get_data_addr(texture.img, &(int){0},
	    &(int){0}, &(int){0});
    return (texture);
}
