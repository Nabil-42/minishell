/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:37:06 by nabil             #+#    #+#             */
/*   Updated: 2024/06/27 08:47:59 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

void update_quote_state(char ch, int *in_single_quotes, int *in_double_quotes)
{
    if (ch == '\'')
    {
        if (*in_single_quotes)
            *in_single_quotes = 0;
        else if (!*in_double_quotes)
            *in_single_quotes = 1;
    }
    else if (ch == '"')
    {
        if (*in_double_quotes)
            *in_double_quotes = 0;
        else if (!*in_single_quotes)
            *in_double_quotes = 1;
    }
}


int is_redirection(char *str, int index)
{
    if (str[index] == '<' || str[index] == '>')
    {
        if (str[index] == '<' && str[index + 1] == '<')
            return 2; 
        else if (str[index] == '>' && str[index + 1] == '>')
            return 2; 
        else
            return 1;
    }
    return 0; 
}


int count_redirections(char *str)
{
    int count = 0;
    int i = 0;
    int in_single_quotes = 0;
    int in_double_quotes = 0;

    while (str[i] != '\0')
    {
        update_quote_state(str[i], &in_single_quotes, &in_double_quotes);

        if (!in_single_quotes && !in_double_quotes)
        {
            int redirection_type = is_redirection(str, i);
            if (redirection_type > 0)
            {
                count += redirection_type;
                if (redirection_type == 2) 
                    i++;
            }
        }
        i++;
    }
    return count;
}



