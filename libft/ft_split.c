/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:06:05 by obritany          #+#    #+#             */
/*   Updated: 2020/11/15 12:42:43 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_words_number(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		while (*s && *s != c)
			s++;
		count++;
	}
	return (count);
}

static char	*get_next_word(char const *s, size_t len)
{
	char	*rslt;
	size_t	k;

	rslt = malloc(sizeof(char) * (len + 1));
	if (rslt == 0)
		return (0);
	k = 0;
	while (k < len)
	{
		rslt[k] = s[k];
		k++;
	}
	rslt[k] = '\0';
	return (rslt);
}

static char	**free_mem(char **rslt, size_t i)
{
	while (i--)
		free(rslt[i]);
	free(rslt);
	return (0);
}

static char	**add_words(const char *s, char c, size_t wnumb, char **rslt)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < wnumb)
	{
		while (*s && *s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		rslt[i] = get_next_word(s, len);
		if (!rslt[i])
			return (free_mem(rslt, i));
		s += len;
		i++;
	}
	rslt[i] = 0;
	return (rslt);
}

char	**ft_split(char const *s, char c)
{
	char	**rslt;
	size_t	wnumb;

	if (!s)
		return (0);
	wnumb = get_words_number(s, c);
	rslt = malloc(sizeof(char *) * (wnumb + 1));
	if (!rslt)
		return (0);
	return (add_words(s, c, wnumb, rslt));
}
