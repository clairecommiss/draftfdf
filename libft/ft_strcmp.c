/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:50:27 by ccommiss          #+#    #+#             */
/*   Updated: 2018/11/14 14:06:10 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *str1, const char *str2)
{
	size_t i;

	i = 0;
	if (str1[0] == '\0' && str2[0] == '\0')
		return (0);
	while (str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	return (((unsigned char)str1[i]) - ((unsigned char)str2[i]));
}
