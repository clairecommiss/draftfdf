/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 17:47:11 by ccommiss          #+#    #+#             */
/*   Updated: 2018/11/15 16:31:51 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	n;
	size_t	k;
	char	*str;
	char	*newstr;

	if (s == NULL)
		return (NULL);
	i = 0;
	k = 0;
	str = (char *)s;
	n = ft_strlen(str);
	while (str[i] == 32 || str[i] == 10 || str[i] == 9)
		i++;
	while ((str[n] == 32 || str[n] == 10 || str[n] == 9 || str[n] == 0) && n)
		n--;
	if (n == 0)
		i = 0;
	if (!(newstr = (char *)malloc((sizeof(char) * (n - i + 2)))))
		return (0);
	while ((i <= n) && n != 0)
		newstr[k++] = str[i++];
	newstr[k] = '\0';
	return (newstr);
}
