/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:19:05 by ccommiss          #+#    #+#             */
/*   Updated: 2018/11/15 14:59:09 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t both;

	i = 0;
	j = 0;
	both = ft_strlen(dst) + ft_strlen(src);
	if (size < ft_strlen(dst))
		return (size + ft_strlen(src));
	else if (size >= ft_strlen(dst))
	{
		while (dst[i] != '\0')
			i++;
		while (src[j] != '\0' && (i + j) < size - 1)
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
		return (both);
	}
	return (0);
}
