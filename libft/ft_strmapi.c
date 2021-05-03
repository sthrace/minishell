/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:49:17 by obritany          #+#    #+#             */
/*   Updated: 2020/11/07 17:49:54 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rslt;
	size_t	i;

	if (!s || !f)
		return (0);
	rslt = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (rslt == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		rslt[i] = f(i, s[i]);
		i++;
	}
	rslt[i] = '\0';
	return (rslt);
}
