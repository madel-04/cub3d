/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:19:50 by madel-va          #+#    #+#             */
/*   Updated: 2025/06/11 13:47:59 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	trim_newline(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
		str[--len] = '\0';
}

int	has_valid_textures(char **textures, t_config *config, t_game *game)
{
	int		i;

	(void)config;
	(void)game;
	i = 0;
	while (i < 4)
	{
		if (!textures[i] || ft_strlen(textures[i]) < 5)
			return (0);
		trim_newline(textures[i]);
		printf("%s\n", textures[i]);
		if (ft_strncmp(textures[i] + ft_strlen(textures[i]) - 4,
				".xpm", 4) != 0)
			return (0);
		i++;
	}
	return (1);
}
