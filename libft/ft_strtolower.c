/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 21:48:39 by obritany          #+#    #+#             */
/*   Updated: 2020/12/02 21:48:41 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *str)
{
	char	*rslt;

	if (!str)
		return (0);
	rslt = str;
	while (*str)
	{
		*str = ft_tolower(*str);
		str++;
	}
	return (rslt);
}
