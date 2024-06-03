/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:52:42 by tissad            #+#    #+#             */
/*   Updated: 2024/04/23 10:34:13 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include <stdlib.h>
# include <stdarg.h>

# define UINT	unsigned int
# define ULONG	unsigned long
# define HEXA	"0123456789abcdef"
# define HEXAX	"0123456789ABCDEF"
# define DEC	"0123456789"
# define CONV	"cspdiuxX%"

typedef struct s_base
{
	const char		*str;
	unsigned long	len;
}	t_base;

int		ft_i_convert(int fd, long n, const char *base, int *flags);
int		ft_print_res(int fd, char *str);
char	*ft_ltoa_b(long n, const char *base);
char	*ft_ultoa_b(ULONG un, const char *base);
char	*printf_justify(const char *s, int nb, char v);
char	*printf_width_str(const char *s, int min);

#endif
