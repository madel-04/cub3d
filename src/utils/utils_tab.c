/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:12:38 by madel-va          #+#    #+#             */
/*   Updated: 2025/06/11 14:12:38 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	ft_count_tabs(const char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			count++;
		i++;
	}
	return (count);
}

static void	ft_copy_with_spaces(const char *src, char *dst)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\t')
		{
			dst[j++] = ' ';
			dst[j++] = ' ';
			dst[j++] = ' ';
			dst[j++] = ' ';
		}
		else
			dst[j++] = src[i];
		i++;
	}
	dst[j] = '\0';
}

char	*ft_tabtospaces(char *str)
{
	size_t	len;
	size_t	tabs;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	tabs = ft_count_tabs(str);
	new_str = malloc(len + (tabs * 3) + 1);
	if (!new_str)
		return (NULL);
	ft_copy_with_spaces(str, new_str);
	return (new_str);
}
