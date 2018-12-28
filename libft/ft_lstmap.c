/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:56:35 by ccommiss          #+#    #+#             */
/*   Updated: 2018/11/17 17:11:37 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *tmp;
	t_list *final;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new = f(lst);
	final = new;
	tmp = lst->next;
	while (tmp != NULL)
	{
		new->next = f(tmp);
		new = new->next;
		tmp = tmp->next;
	}
	return (final);
}
