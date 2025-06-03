/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:39:10 by madel-va          #+#    #+#             */
/*   Updated: 2025/06/02 11:47:18 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_config(t_config *config)
{
	int	i;

	if (!config)
		return ;
	if (config->map_lines)
	{
		i = 0;
		while (config->map_lines[i])
			free(config->map_lines[i++]);
		free(config->map_lines);
	}
	i = 0;
	while (i < 4 && config->textures[i])
		free(config->textures[i++]);
}
