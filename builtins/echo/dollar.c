/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:06:47 by nabil             #+#    #+#             */
/*   Updated: 2024/06/19 12:22:06 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"


int handle_direction(char *str, int i, t_echo *eko)
{
    if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
    {
        eko->line[eko->j] = '\0';
        direction_double(str, i, eko);
        return 1;
    }
    if (str[i] == '>' || str[i] == '<')
    {
        eko->line[eko->j] = '\0';
        direction(str, i, eko);
        return 1;
    }
    return 0;
}

char *extract_env_variable_name(char *str, int *i)
{
    char *variable_env = malloc(PATH_MAX + 1);
    int k = 0;

    if (variable_env == NULL)
        return NULL;

    ++(*i);
    while (((str[*i] >= 'A' && str[*i] <= 'Z')
        || (str[*i] >= 'a' && str[*i] <= 'z')) && str[*i] != '\0')
    {
        variable_env[k] = str[*i];
        ++*i;
        k++;
    }
    variable_env[k] = '\0';
    return variable_env;
}

int handle_variable_expansion(char *str, t_echo *eko, int *i)
{
    char *variable_env;
    char *name;
    
    variable_env = extract_env_variable_name(str, i);
    if (variable_env == NULL)
        return 0;

    name = getenv(variable_env);
    free(variable_env);

    if (name == NULL)
        return 0;

    int k = 0;
    while (name[k])
    {
        eko->line[eko->j++] = name[k++];
    }
    return 1;
}
void copy_normal_char(char *str, t_echo *eko, int *i)
{
    char *itoua;
    int k;
    if (str[*i] == '$' && str[*i + 1] == '?')
        {
            k = 0;
            itoua = ft_itoa(eko->$);
            while (itoua[k])
            {
                eko->line[eko->j] = itoua[k];
                ++eko->j;
                k++;
            }
            ++*i;
        }
    else (eko->line[eko->j++] = str[*i]);
    ++(*i);
}
int dollar(char *str, t_echo *eko)
{
    int i = 0;
    eko->j = 0;

    while (str[i])
    {
        if (handle_direction(str, i, eko))
            return 0;

        if (str[i] == '$' && str[i + 1] != '\0' && str[eko->i + 1] != '?')
        {
            
            if (!handle_variable_expansion(str, eko, &i))
                return 0;
            continue;
        }

        copy_normal_char(str, eko, &i);
    }

    eko->line[eko->j] = '\0';
    printf("%s\n", eko->line);
    return 0;
}







