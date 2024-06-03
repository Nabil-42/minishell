/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils1_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <issad.tahar@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:08:34 by tissad            #+#    #+#             */
/*   Updated: 2024/02/06 10:01:38 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_inc/ft_printf_utils.h"
#include "../includes/libft.h"

char	*printf_justify(const char *s, int nb, char v)
{
	int		len;
	char	*res;
	int		size;

	if (nb < 0)
		size = nb * -1;
	else
		size = nb;
	len = ft_strlen(s);
	if (size <= len)
		return (ft_strdup(s));
	res = malloc(sizeof (char) * (size + 1));
	if (!res)
		return (NULL);
	ft_memset(res, v, size);
	if (nb < 0)
		ft_memcpy(res, s, len);
	else
		ft_memcpy(&res[size - len], s, len);
	res[size] = 0;
	return (res);
}

char	*printf_width_str(const char *s, int min)
{
	int		len;
	char	*res;

	if (!s)
		return (ft_strdup(""));
	len = ft_strlen(s);
	if (min >= len || min == -1)
		return (ft_strdup(s));
	res = malloc(sizeof (char) * (min + 1));
	if (!res)
		return (NULL);
	ft_memcpy(res, s, min);
	res[min] = 0;
	return (res);
}
