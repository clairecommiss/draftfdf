/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:55:45 by ccommiss          #+#    #+#             */
/*   Updated: 2018/11/09 16:24:55 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *tofind)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (tofind[0] == '\0')
		return ((char*)(str));
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == tofind[j])
		{
			j++;
			if (tofind[j] == '\0')
				return ((char*)(str + i));
		}
		i++;
	}
	return (0);
}
