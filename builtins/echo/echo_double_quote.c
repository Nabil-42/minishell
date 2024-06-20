/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_double_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:12:19 by nabil             #+#    #+#             */
/*   Updated: 2024/06/20 08:30:23 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

int handle_consecutive_quotes(char *str, t_echo *eko)
{
    if (str[eko->i] == '"' && str[eko->i + 1] == '"')
    {
        eko->line[eko->j] = ' ';
        eko->i += 2;
        return 2;
    }
    return 0;
}

int handle_single_double_quote(char *str, t_echo *eko, int *flag)
{
    if (str[eko->i] == '"')
    {
        ++(*flag);
        if (*flag == 1)
        {
            ++eko->i;
        }
        else
        {
            ++eko->i;
            eko->line[eko->j] = '\0';
            return 0;
        }
    }
    return 1;
}

void copy_non_special_char(char *str, t_echo *eko)
{
    char *itoua;
    int k;
    if (str[eko->i] == '$' && str[eko->i + 1] == '?')
        {
            k = 0;
            itoua = ft_itoa(eko->$);
            while (itoua[k])
            {
                eko->line[eko->j] = itoua[k];
                ++eko->j;
                k++;
            }
            --eko->j;
            ++eko->i;
        }
    else (eko->line[eko->j] = str[eko->i]);
    if (str[eko->i] == '$' && str[eko->i + 1] == ' ')
        {
            ++eko->j;
            eko->line[eko->j] = ' ';
        }
    ++eko->i;
    ++eko->j;
}

int echo_take_of_double_quote(char *str, t_echo *eko, int n)
{
    int flag = 0;
    int dollar_check;
    int result = 0;

    while (eko->i <= n)
    {
        result = handle_consecutive_quotes(str, eko);
        if (result == 2)
            return 2;

        result = handle_single_double_quote(str, eko, &flag);
        if (result == 0)
            return 0;

        dollar_check = dollar_double(str, eko);
        if (dollar_check == -1)
            return -1;

        if (dollar_check > 0)
            continue;

        copy_non_special_char(str, eko);
    }

    return 0;
}



