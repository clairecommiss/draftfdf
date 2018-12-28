/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 16:46:09 by ccommiss          #+#    #+#             */
/*   Updated: 2018/11/15 16:56:40 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (tofind[0] == '\0')
		return ((char*)(str));
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		while (str[i + j] == tofind[j] && (i + j) < len)
		{
			j++;
			if (tofind[j] == '\0')
				return ((char*)(str + i));
		}
		i++;
	}
	return (0);
}
