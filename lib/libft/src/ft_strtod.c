/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:18:36 by tissad            #+#    #+#             */
/*   Updated: 2024/04/12 18:07:24 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_check_str(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ((str[i] == ' ') || \
		(str[i] >= '\t' && str[i] <= '\r') || str[i] == '-'))
			i++;
		if (ft_isdigit(str[i]) || str[i] == '.')
		{
			if (str[i] == '.')
				count++;
			if (count > 1)
				return ((char *)&str[i + 1]);
			i++;
		}
		else
			return ((char *)&str[i + 1]);
	}
	return ((char *)&str[i + 1]);
}

double	ft_strtod(const char *str, char **endptr)
{
	char	buf[512];
	char	*ptr;
	double	d;
	double	f;

	buf[0] = 0;
	f = 0.;
	ptr = ft_check_str(str);
	ft_strlcpy(buf, str, ptr - str);
	if (endptr)
		*endptr = ptr;
	ptr = strchr(buf, '.');
	d = ft_atoi(buf);
	if (ptr)
		f = (double)ft_atoi(ptr + 1);
	while (f > 1.)
		f /= 10.;
	if (ft_strchr(buf, '-'))
	{
		d *= -1;
		return ((double)(-1. * ((double)d + f)));
	}
	return ((double)d + f);
}
