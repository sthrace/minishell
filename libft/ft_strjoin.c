/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:45:49 by obritany          #+#    #+#             */
/*   Updated: 2020/11/07 17:47:09 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rslt;
	char	*temp;

	if (!s1 || !s2)
		return (0);
	rslt = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (rslt == 0)
		return (0);
	temp = rslt;
	while (*s1)
	{
		*temp = *s1;
		temp++;
		s1++;
	}
	while (*s2)
	{
		*temp = *s2;
		temp++;
		s2++;
	}
	*temp = '\0';
	return (rslt);
}
