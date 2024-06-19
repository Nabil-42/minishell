/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:04:33 by tissad            #+#    #+#             */
/*   Updated: 2024/06/19 13:01:51 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../ft_printf_inc/ft_printf_convert.h"

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	if (!str)
		return (-1);
	va_start(args, str);
	count = ft_printf_bis(STDOUT_FILENO, str, args);
	va_end(args);
	return (count);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	int		count;
	va_list	args;

	if (!str)
		return (-1);
	va_start(args, str);
	count = ft_printf_bis(fd, str, args);
	va_end(args);
	return (count);
}
