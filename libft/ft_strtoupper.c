/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 21:48:49 by obritany          #+#    #+#             */
/*   Updated: 2020/12/02 21:48:53 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtoupper(char *str)
{
	char	*rslt;

	if (!str)
		return (0);
	rslt = str;
	while (*str)
	{
		*str = ft_toupper(*str);
		str++;
	}
	return (rslt);
}
