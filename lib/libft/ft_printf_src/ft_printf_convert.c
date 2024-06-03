/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:38:47 by tissad            #+#    #+#             */
/*   Updated: 2024/04/23 10:34:52 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_inc/ft_printf_utils.h"
#include "../ft_printf_inc/ft_printf_get_flags.h"
#include "../includes/libft.h"

static int	ft_c_convert(int fd, char c, int *flags)
{
	int	size;

	size = 1;
	if (flags[MINUS] > 0)
	{
		while (size < flags[MINUS])
		{
			ft_putchar_fd(' ', fd);
			size++;
		}
	}
	ft_putchar_fd(c, fd);
	if (flags[MINUS] < 0)
	{
		while (size < (-flags[MINUS]))
		{
			ft_putchar_fd(' ', fd);
			size++;
		}
	}
	return (size);
}

static int	ft_s_convert(int fd, const char *str, int *flags)
{
	char	*res;
	char	*tmp;
	int		len;

	if (!str && (flags[DOT] >= 6 || flags[DOT] == -1))
		res = printf_justify("(null)", flags[MINUS], ' ');
	else
	{
		tmp = printf_width_str(str, flags[DOT]);
		res = printf_justify(tmp, flags[MINUS], ' ');
		free(tmp);
	}
	len = ft_print_res(fd, res);
	free(res);
	return (len);
}

static int	ft_p_convert(int fd, long add, int *flags)
{
	char	*res;
	char	*tmp;
	int		size;

	size = 0;
	if (add == 0)
		res = printf_justify("(nil)", flags[MINUS], ' ');
	else
	{
		res = ft_ultoa_b(add, HEXA);
		tmp = ft_strjoin("0x", res);
		free(res);
		res = printf_justify(tmp, flags[MINUS], ' ');
		free(tmp);
	}
	size = ft_print_res(fd, res);
	free(res);
	return (size);
}

static int	ft_convert(int fd, va_list args, int *flags)
{
	if (flags[CONVERT] == 'c')
		return (ft_c_convert(fd, (char) va_arg(args, int), flags));
	if (flags[CONVERT] == 's')
		return (ft_s_convert(fd, va_arg(args, char *), flags));
	if (flags[CONVERT] == 'p')
		return (ft_p_convert(fd, va_arg(args, long), flags));
	if (flags[CONVERT] == 'd' || flags[CONVERT] == 'i')
		return (ft_i_convert(fd, va_arg(args, int), DEC, flags));
	if (flags[CONVERT] == 'u')
		return (ft_i_convert(fd, va_arg(args, UINT), DEC, flags));
	if (flags[CONVERT] == 'x')
		return (ft_i_convert(fd, va_arg(args, UINT), HEXA, flags));
	if (flags[CONVERT] == 'X')
		return (ft_i_convert(fd, va_arg(args, UINT), HEXAX, flags));
	if (flags[CONVERT] == '%')
		return (ft_c_convert(fd, '%', flags));
	return (0);
}

int	ft_printf_bis(int fd, const char *str, va_list args)
{
	int		count;
	char	*iter;
	int		flags[NFLAGS];

	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			iter = ft_get_flags(str, flags);
			count += ft_convert(fd, args, flags);
			str += (iter - str) + 1;
		}
		else
		{
			ft_putchar_fd(*str, fd);
			count++;
			str++;
		}
	}
	return (count);
}
