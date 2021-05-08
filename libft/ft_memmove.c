/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:00:24 by obritany          #+#    #+#             */
/*   Updated: 2020/11/07 17:03:32 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*mydest;

	if (!dst && !src && len > 0)
		return (0);
	mydest = dst;
	if (mydest < src)
		while (len--)
			*(char *)mydest++ = *(char *)src++;
	else
	{
		mydest += len - 1;
		src += len - 1;
		while (len--)
			*(char *)mydest-- = *(char *)src--;
	}
	return (dst);
}
