/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <issad.tahar@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:16:00 by tissad            #+#    #+#             */
/*   Updated: 2024/02/05 10:37:29 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_GET_FLAGS_H
# define FT_PRINTF_GET_FLAGS_H

/*==================================Flags=====================================*/
# define IFLAGS "+ #"
# define NFLAGS	    7
# define ZERO	    0
# define MINUS	    1
# define DOT	    2
# define SPACE	    3
# define HTAG	    4
# define DOTE	    5
# define CONVERT    6

/*============================================================================*/
char	*ft_get_flags(const char *str, int *flags);

#endif