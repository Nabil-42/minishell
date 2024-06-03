/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <issad.tahar@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:13:00 by tissad            #+#    #+#             */
/*   Updated: 2024/02/06 09:59:43 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_inc/ft_printf_get_flags.h"
#include "../includes/libft.h"

char	*ft_get_zero(char *str, int *flags)
{
	if (*str && (*str == '0' || ft_strchr(IFLAGS, *str)))
	{
		while (*str && (*str == '0' || ft_strchr(IFLAGS, *str)))
		{
			if (*str == '0')
				flags[ZERO] += 1;
			if (*str == ' ')
				flags[SPACE] = (int)*str;
			if (*str == '+')
				flags[SPACE] = (int)*str;
			if (*str == '#')
				flags[HTAG] += 1;
			str++;
		}
	}
	return (str);
}

char	*ft_get_minus(char *str, int *flags)
{
	flags[MINUS] = 1;
	while (*str && (*str == '-' || ft_strchr(IFLAGS, *str)))
	{
		if (*str == '-')
			flags[MINUS] = -1;
		if (*str == ' ')
			flags[SPACE] = (int)*str;
		if (*str == '+')
			flags[SPACE] = (int)*str;
		if (*str == '#')
			flags[HTAG] += 1;
		str++;
	}
	flags[MINUS] *= ft_atoi(str);
	if (*str && ft_isdigit(*str))
	{
		while (*str && (*str >= '0' && *str <= '9'))
			str++;
	}
	return (str);
}

char	*ft_get_dot(char *str, int *flags)
{
	if (*str && *str == '.')
	{
		flags[DOTE] = 1;
		str++;
	}
	else
		flags[DOT] = -1;
	if (*str && (*str >= '0' && *str <= '9'))
		flags[DOT] = ft_atoi(str);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	return (str);
}

char	*ft_get_flags(const char *str, int *flags)
{
	char	*iterator;

	ft_memset(flags, 0, sizeof(int) * NFLAGS);
	iterator = (char *)str;
	flags[CONVERT] = *iterator;
	iterator = ft_get_zero(iterator, flags);
	iterator = ft_get_minus(iterator, flags);
	iterator = ft_get_dot(iterator, flags);
	return (iterator);
}
