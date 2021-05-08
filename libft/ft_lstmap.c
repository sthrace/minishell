/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:50:56 by obritany          #+#    #+#             */
/*   Updated: 2020/11/15 12:19:43 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rslt;
	t_list	*temp;

	if (!f)
		return (0);
	rslt = 0;
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (temp == 0)
		{
			ft_lstclear(&rslt, del);
			return (0);
		}
		ft_lstadd_back(&rslt, temp);
		lst = lst->next;
	}
	return (rslt);
}
