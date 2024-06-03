/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert_i.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:40:29 by tissad            #+#    #+#             */
/*   Updated: 2024/04/23 10:36:06 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_inc/ft_printf_utils.h"
#include "../ft_printf_inc/ft_printf_get_flags.h"
#include "../includes/libft.h"

int	ft_print_res(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
	return (i);
}

static char	*ft_minusi_convert(long n, const char *base, int *flags)
{
	char	*tmp;
	char	*res;
	char	v;

	v = ' ';
	tmp = ft_ltoa_b(n, base);
	if (flags[ZERO] && flags[MINUS] > 0)
	{
		v = '0';
		if (n < 0)
			tmp[0] = v;
	}
	if (n >= 0 && flags[SPACE] != 0 && flags[MINUS] <= (int)ft_strlen(tmp))
		flags[MINUS] = ft_strlen(tmp) + 1;
	res = printf_justify(tmp, flags[MINUS], v);
	if (n < 0 && v == '0')
		res[0] = '-';
	if (n >= 0 && flags[SPACE] != 0)
		res[0] = (char)flags[SPACE];
	free(tmp);
	return (res);
}

static char	*ft_doti_convert(long n, const char *base, int *flags)
{
	char	*tmp;
	char	*res;

	if (flags[DOTE] && flags[DOT] == 0 && n == 0)
		res = ft_strdup("");
	else
		res = ft_ltoa_b(n, base);
	if (n < 0 && flags[DOT] >= (int)ft_strlen(res))
	{
		res[0] = '0';
		flags[DOT] += 1;
	}
	tmp = printf_justify(res, flags[DOT], '0');
	free(res);
	if (n < 0)
		tmp[0] = '-';
	if (n > 0 && flags[SPACE] && flags[MINUS] <= (int)ft_strlen(tmp))
		res = printf_justify(tmp, ft_strlen(tmp), (char)flags[SPACE]);
	res = printf_justify(tmp, flags[MINUS], ' ');
	free(tmp);
	return (res);
}

int	ft_i_convert(int fd, long n, const char *base, int *flags)
{
	char	*res;
	char	*tmp;
	int		size;

	size = 0;
	if (flags[CONVERT] == 'u' || flags[CONVERT] == 'x' \
	|| flags[CONVERT] == 'X')
		flags[SPACE] = 0;
	if (flags[DOT] != -1)
		tmp = ft_doti_convert(n, base, flags);
	else
		tmp = ft_minusi_convert(n, base, flags);
	if (flags[CONVERT] == 'x' && flags[HTAG] && n > 0)
		res = ft_strjoin("0x", tmp);
	else if (flags[CONVERT] == 'X' && flags[HTAG] && n > 0)
		res = ft_strjoin("0X", tmp);
	else
		res = ft_strdup(tmp);
	free(tmp);
	size = ft_print_res(fd, res);
	free (res);
	return (size);
}
