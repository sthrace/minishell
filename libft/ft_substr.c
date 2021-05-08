/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:52:33 by obritany          #+#    #+#             */
/*   Updated: 2020/11/07 17:53:56 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rslt;
	char	*temp;
	size_t	slen;
	size_t	rlen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	rlen = len;
	if ((start + len) > slen)
		rlen = slen - start;
	rslt = malloc((rlen + 1) * sizeof(char));
	if (rslt == 0)
		return (0);
	while (start--)
		s++;
	temp = rslt;
	while (rlen--)
		*temp++ = *s++;
	*temp = '\0';
	return (rslt);
}
