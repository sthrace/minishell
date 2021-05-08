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

static int	get_len(int n)
{
	int	tmp;
	int	len;

	tmp = n / 10;
	len = 1;
	while (tmp)
	{
		len++;
		tmp = tmp / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*rslt;
	int		tmp;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = get_len(n);
	tmp = 0;
	if (n < 0)
		tmp = 1;
	rslt = malloc(sizeof(char) * (len + 1 + tmp));
	if (!rslt)
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
