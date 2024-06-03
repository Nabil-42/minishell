/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils0_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <issad.tahar@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:38:35 by tissad            #+#    #+#             */
/*   Updated: 2024/03/19 10:48:01 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_inc/ft_printf_utils.h"
#include "../includes/libft.h"

static int	ltoa_bis(ULONG un, char *toa, int i, t_base *base);

char	*ft_ltoa_b(long n, const char *base)
{
	ULONG	un;
	char	toa[512];
	t_base	base_len;
	int		size;

	base_len.str = base;
	base_len.len = ft_strlen(base);
	size = 0;
	if (n < 0)
	{
		toa[size] = '-';
		(size)++;
		un = (unsigned long)(-n);
	}
	else
		un = (unsigned long) n;
	size = ltoa_bis(un, toa, size, &base_len);
	toa[size] = '\0';
	return (ft_strdup(toa));
}

char	*ft_ultoa_b(ULONG un, const char *base)
{
	int		size;
	char	toa[512];
	t_base	base_len;

	base_len.str = base;
	base_len.len = ft_strlen(base);
	size = 0;
	toa[0] = 0;
	size = ltoa_bis(un, toa, size, &base_len);
	toa[size] = '\0';
	return (ft_strdup(toa));
}

static int	ltoa_bis(ULONG un, char *toa, int i, t_base *base)
{
	unsigned long	r;
	unsigned long	q;

	r = un % base->len;
	q = un / base->len;
	if (q == 0)
	{
		toa[i] = (base->str[r]);
		return (i + 1);
	}
	i = ltoa_bis(q, toa, i, base);
	toa[i] = base->str[r];
	return (i + 1);
}
