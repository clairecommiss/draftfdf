/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:42:59 by ccommiss          #+#    #+#             */
/*   Updated: 2018/11/16 13:21:17 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_number(int n)
{
	int	i;

	i = 1;
	while (n % 10 != n)
	{
		i++;
		n = n / 10;
	}
	if (n < 0)
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	char	*res;
	int		num;
	int		i;

	i = ft_number(n);
	num = n;
	if (!(res = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	res[i] = '\0';
	i--;
	while (i != -1)
	{
		if (num < 0)
			res[i] = (-(num % 10) + 48);
		else
			res[i] = (num % 10 + 48);
		i--;
		num = num / 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
