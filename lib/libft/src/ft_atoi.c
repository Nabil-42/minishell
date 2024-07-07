/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:02:13 by tissad            #+#    #+#             */
/*   Updated: 2024/07/07 11:08:15 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sig;
	int	nb;

	sig = 1;
	nb = 0;
	while (*str)
	{
		while ((*str == ' ') || (*str >= '\t' && *str <= '\r'))
			str++;
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				sig *= -1;
			str++;
		}
		while (*str >= '0' && *str <= '9')
		{
			nb = nb * 10 + (int)(*str - '0');
			str++;
		}
		break ;
	}
	return (nb * sig);
}

int	ft_atoi_bis(const char *str)
{
	int	sig;
	int	nb;

	sig = 1;
	nb = 0;
	while (*str)
	{
		while ((*str == ' ') || (*str >= '\t' && *str <= '\r'))
			str++;
		if (*str == '"')
			str++;
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				sig *= -1;
			str++;
		}
		if (*str == '"')
			str++;
		while (*str >= '0' && *str <= '9')
			(nb = nb * 10 + (int)(*str - '0'),
					str++);
		break ;
	}
	return (nb * sig);
}
