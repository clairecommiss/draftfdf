/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:08:36 by ccommiss          #+#    #+#             */
/*   Updated: 2018/11/16 11:18:01 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*src;
	unsigned char			letter;
	size_t					i;

	i = 0;
	src = (const unsigned char *)s;
	letter = (unsigned char)c;
	while (i < n)
	{
		if (src[i] == letter)
			return ((void *)src + i);
		i++;
	}
	return (NULL);
}
