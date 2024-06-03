/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <issad.tahar@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:51:11 by tissad            #+#    #+#             */
/*   Updated: 2024/02/06 09:38:33 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	init(t_buf *inter, int max)
{
	inter->buf = malloc(sizeof (char) * (max));
	if (!inter->buf)
		return (0);
	inter->buf[0] = 0;
	inter->size = 0;
	inter->max = max;
	return (1);
}

int	add_one(t_buf *inter, char *buffer, int n)
{
	char	*tmp;

	if (inter->size + n >= inter->max)
	{
		tmp = inter->buf;
		if (!init(inter, (inter->size + n) * 3))
		{
			free(buffer);
			return (0);
		}
		inter->size = ft_strlcat(inter->buf, tmp, inter->max);
		free(tmp);
		tmp = NULL;
	}
	inter->size += ft_strlcat(inter->buf, buffer, inter->max);
	return (1);
}

int	read_line(int fd, t_buf *inter, char *buffer)
{
	int		n;
	char	*nl;

	nl = ft_strchr(inter->buf, '\n');
	while (!nl)
	{
		buffer[0] = 0;
		n = read(fd, buffer, BUFFER_SIZE);
		if (n <= 0)
		{
			if (inter->size)
				return (1);
			free(inter->buf);
			return (0);
		}
		buffer[n] = 0;
		if (!add_one(inter, buffer, n))
			return (0);
		nl = ft_strchr(buffer, '\n');
	}
	return (1);
}

char	*get_line(char *rest, t_buf *inter)
{
	char	*nl;

	rest[0] = 0;
	nl = ft_strchr(inter->buf, '\n');
	if (nl)
	{
		ft_strlcat(rest, (nl + 1), BUFFER_SIZE + 1);
		*((nl) + 1) = 0;
	}
	return (ft_strdup(inter->buf));
}

char	*get_next_line(int fd)
{
	char		*res;
	static char	buffer[BUFFER_SIZE + 1];
	t_buf		buf_inter;

	if (!init(&buf_inter, BUFFER_MAX))
		return (NULL);
	if (!add_one(&buf_inter, buffer, BUFFER_SIZE + 1))
		return (NULL);
	if (!read_line(fd, &buf_inter, buffer))
		return (NULL);
	res = get_line(buffer, &buf_inter);
	free(buf_inter.buf);
	return (res);
}
