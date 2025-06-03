/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:19:50 by madel-va          #+#    #+#             */
/*   Updated: 2025/06/02 11:41:28 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_valid_textures(char **textures)
{
    int	i;

    i = 0;
    while (i < 4)
    {
        if (!textures[i] || ft_strlen(textures[i]) < 5)
            return (0); // Textura no válida o demasiado corta
        if (ft_strncmp(textures[i] + ft_strlen(textures[i]) - 5, ".xpm", 4) != 0)
            return (0); // Formato de textura no válido
        // ! Intentar abrir el archivo de textura
        i++;
    }
    return (1);
}