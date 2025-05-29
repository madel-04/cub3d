/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:48:45 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/29 20:48:45 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	count;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	count = ft_strlen(s1) + ft_strlen(s2);
	j = 0;
	if (!count)
		return (0);
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (0);
	while (*s1)
		str[j++] = *(s1++);
	while (*s2)
		str[j++] = *(s2++);
	str[j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	length;

	length = len;
	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) - start <= length)
		length = ft_strlen(s) - start;
	if (ft_strlen(s) <= (int)start)
	{
		start = 0;
		length = 0;
	}
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (!str)
		return (0);
	while (s[start] && length--)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
