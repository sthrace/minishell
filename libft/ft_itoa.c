/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:43:22 by obritany          #+#    #+#             */
/*   Updated: 2020/11/07 16:45:34 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*rslt;
	int		tmp;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	tmp = n;
	len = 1;
	while ((tmp = tmp / 10))
		len++;
	tmp = (n < 0) ? 1 : 0;
	if ((rslt = malloc(sizeof(char) * (len + 1 + tmp))) == 0)
		return (0);
	if (n < 0)
	{
		rslt[0] = '-';
		n *= -1;
	}
	rslt[len + tmp] = '\0';
	while (len--)
	{
		rslt[len + tmp] = n % 10 + '0';
		n = n / 10;
	}
	return (rslt);
}
