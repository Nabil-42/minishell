/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:14:24 by nabil             #+#    #+#             */
/*   Updated: 2024/07/04 18:02:49 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"

void skip_spaces(char *str, int *i)
{
    while (str[*i] && str[*i] == ' ')
    {
        (*i)++;
    }
}

char *get_next_token(char *str, int *i)
{
    int quote = 0;
    int start = *i;
    while (str[*i] && (str[*i]))
    {
    // printf("ici %c\n", str[*i]);
        if (str[*i] == '"')
            quote += 1;
        (*i)++;
    }
    int len = *i - start;
    char *token = malloc(len + 1);
    if (!token)
    {
        return NULL;
    }
    strncpy(token, str + start, len);
    token[len] = '\0';
    return token;
}

void handle_quotes_file(char c, int *in_single_quotes, int *in_double_quotes)
{
    if (c == '\'' && !(*in_double_quotes))
    {
        *in_single_quotes = !(*in_single_quotes);
    }
    else if (c == '"' && !(*in_single_quotes))
    {
        *in_double_quotes = !(*in_double_quotes);
    }
}

char **split_file(char *str, int *result_size)
{
    char **result = malloc(PATH_MAX * sizeof(char *));
    int len = strlen(str);
    int in_single_quotes = 0, in_double_quotes = 0;
    int i = 0;

    *result_size = 0;
    if (!result)
    {
        return NULL;
    }

    while (i < len)
    {
        handle_quotes_file(str[i], &in_single_quotes, &in_double_quotes);

        if (!in_single_quotes && !in_double_quotes && is_redirection(str[i]))
        {
            // Skip the redirection symbol
            while (str[i] && is_redirection(str[i]))
            {
                i++;
            }
            // Skip spaces after redirection
            skip_spaces(str, &i);
            // Get the next token (target of redirection)
            if (str[i] && str[i] != ' ')
            {
                
                char *token = get_next_token(str, &i);
                if (token)
                {
                    result[*result_size] = token;
                    (*result_size)++;
                }
            }
        }
        else
        {
            i++;
        }
    }

    result[*result_size] = NULL;
    return result;
}