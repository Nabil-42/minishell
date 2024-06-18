/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_simple_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/18 23:03:47 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"

int echo_take_of_simple_quote(char *str, t_echo *eko, int n)
{
	int flag;
        flag = 0;
        while(eko->i <= n)
        {
                if (str[eko->i] == 39 && str[eko->i + 1] == 39)
                {
                        eko->i += 2;
                        eko->line[eko->j] = ' ';
                        return (2);
                }
                if (str[eko->i] == 39)
                {
                        ++flag;
                        if (flag == 1)
                                ++eko->i;
                        else{
                                ++eko->i;
                                eko->line[eko->j] = '\0';
                                return (0);
                        }
                }
                eko->line[eko->j] = str[eko->i];
                (++eko->i, ++eko->j);
        }
        return (0);
}
