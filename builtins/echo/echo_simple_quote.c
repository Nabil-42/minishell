/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_simple_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/20 17:58:55 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"

int	echo_take_of_simple_quote(char *str, t_echo *eko, int n)
{
	int	flag;

	flag = 0;
	while (eko->i <= n)
	{
		if (str[eko->i] == 39 && str[eko->i + 1] == 39)
		{
			eko->i += 2;
			eko->line[eko->j] = '\0';
			return (2);
		}
		if (str[eko->i] == 39)
		{
			++flag;
			if (flag == 1)
				++eko->i;
			else
			{
				++eko->i;
				eko->line[eko->j] = '\0';
				return (0);
			}
		}
		eko->line[eko->j] = str[eko->i];
		if (str[eko->i] == '$' && str[eko->i + 1] == ' ')
		{
			++eko->j;
			eko->line[eko->j] = ' ';
		}
		(++eko->i, ++eko->j);
	}
	return (0);
}
