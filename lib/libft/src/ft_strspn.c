/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <issad.tahar@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:01:43 by tissad            #+#    #+#             */
/*   Updated: 2024/03/05 10:13:45 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	is_delim(char c, char const *delimiters)
{
	while (*delimiters)
	{
		if (c == *delimiters)
			return (1);
		delimiters++;
	}
	return (0);
}

int	ft_strspn(const char *str, const char *delimiters)
{
	int	i;

	i = 0;
	while (str[i] && is_delim(str[i], delimiters))
		i++;
	return (i);
}
