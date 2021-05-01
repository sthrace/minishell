/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 19:56:09 by obritany          #+#    #+#             */
/*   Updated: 2020/12/24 19:56:13 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	read_until(int fd, char **buffer, char **remain, char chr)
{
	ssize_t	rb;
	char	*temp;

	while ((rb = read(fd, *buffer, BUFFER_SIZE)) > 0)
	{
		(*buffer)[rb] = '\0';
		temp = *remain;
		*remain = ft_strjoin(*remain, *buffer);
		free(temp);
		if (*remain == 0)
			return (-1);
		if (ft_strchr(*buffer, chr))
			return (1);
	}
	return (rb);
}

static int	get_remain_line(char **remain, char **line)
{
	char	*p_chr;
	char	*temp;

	p_chr = ft_strchr(*remain, '\n');
	if (p_chr)
	{
		*p_chr = '\0';
		*line = ft_strdup(*remain);
		temp = *remain;
		*remain = ft_strdup(p_chr + 1);
		free(temp);
		if (*line == 0 || *remain == 0)
			return (-1);
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char *remain;
	char		*buffer;
	ssize_t		rslt;

	if (BUFFER_SIZE <= 0)
		return (-1);
	if (remain == 0)
		if (!(remain = ft_strdup("")))
			return (-1);
	if ((rslt = get_remain_line(&remain, line)))
		return (rslt);
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	rslt = read_until(fd, &buffer, &remain, '\n');
	free(buffer);
	if (rslt == -1)
		return (-1);
	if (rslt == 1)
		return (get_remain_line(&remain, line));
	*line = ft_strdup(remain);
	if (*line == 0)
		return (-1);
	free(remain);
	remain = 0;
	return (rslt);
}
