/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:35:38 by ccommiss          #+#    #+#             */
/*   Updated: 2018/11/17 13:29:02 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	if (*alst == NULL)
		return ;
	tmp = *alst;
	while ((*alst) != NULL)
	{
		*alst = (*alst)->next;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = *alst;
	}
	free((*alst));
	*alst = 0;
}
