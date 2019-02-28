/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:30:51 by ccommiss          #+#    #+#             */
/*   Updated: 2019/02/28 17:28:44 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_malloceach(char *str, char **tab, char c)
{
	int i;
	int j;
	int a;

	a = 0;
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != c && str[i])
		{
			a++;
			i++;
		}
		if (a != 0)
		{
			if (!(tab[j] = (char *)malloc(sizeof(char) * a + 1)))
				return (NULL);
			j++;
		}
		i++;
		a = 0;
	}
}

static int			ft_countwords(char *str, char c)
{
	int i;
	int word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if ((str[i] != c) && ((str[i + 1] == c) || str[i + 1] == 0))
		{
			word++;
		}
		i++;
	}
	return (word);
}

static void			fillthetab(char *str, char **tab, char c)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	j = 0;
	while (str[k] != '\0')
	{
		while ((str[k] != c) && str[k])
		{
			tab[i][j] = str[k];
			k++;
			j++;
		}
		if (j != 0)
		{
			tab[i][j] = '\0';
			j = 0;
			i++;
		}
		if (str[k] != '\0')
			k++;
	}
	tab[i] = NULL;
}

char				**ft_strsplit(char const *str, char c)
{
	char **tab;

	if (str == NULL)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *)
		* (ft_countwords((char *)str, c) + 4))))
		return (NULL);
	ft_malloceach((char *)str, tab, c);
	fillthetab((char *)str, tab, c);
	return (tab);
}
