/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:47:18 by obritany          #+#    #+#             */
/*   Updated: 2020/11/07 17:48:03 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dst_len;
	size_t trg_len;

	dst_len = ft_strlen(dst);
	dst += dst_len;
	if (dst_len < dstsize)
		trg_len = dst_len + ft_strlcpy(dst, src, (dstsize - dst_len));
	else
		trg_len = dstsize + ft_strlen(src);
	return (trg_len);
}
