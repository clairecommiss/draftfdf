/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:47:52 by ccommiss          #+#    #+#             */
/*   Updated: 2018/12/27 15:48:00 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strslen(char const *s1, char const *s2)
{
	size_t k;

	if ((s1 == NULL) && (s2 == NULL))
		return (0);
	else if (s1 == NULL)
		k = 1 + ft_strlen(s2);
	else
		k = ft_strlen(s1) + ft_strlen(s2);
	return (k);
}
