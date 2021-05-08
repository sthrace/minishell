/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:59:24 by obritany          #+#    #+#             */
/*   Updated: 2020/11/07 17:00:14 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*mydst;

	if (!dst && !src && n > 0)
		return (0);
	mydst = dst;
	while (n--)
	{
		*mydst = *(char *)src;
		mydst++;
		src++;
	}
	return (dst);
}
