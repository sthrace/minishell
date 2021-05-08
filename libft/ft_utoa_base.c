/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 21:49:40 by obritany          #+#    #+#             */
/*   Updated: 2020/12/02 21:49:42 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa_base(unsigned long n, unsigned int base, char type)
{
	char			*rslt;
	unsigned long	tmp;
	size_t			len;
	char			*nums;

	nums = "0123456789abcdef";
	if (type == 'i')
		n = (unsigned int)n;
	tmp = n / 10;
	len = 1;
	while (tmp)
	{
		len++;
		tmp = tmp / 10;
	}
	rslt = malloc(sizeof(char) * (len + 1));
	if (rslt == 0)
		return (0);
	rslt[len] = '\0';
	while (len--)
	{
		rslt[len] = nums[n % base];
		n = n / base;
	}
	return (rslt);
}
