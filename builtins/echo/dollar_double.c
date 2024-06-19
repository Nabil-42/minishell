/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/19 12:10:59 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

#define PATH_MAX 4096


char* extract_variable_name(char *str, t_echo *eko)
{
    char *variable_env = malloc(PATH_MAX + 1);
    int k = 0;

    if (variable_env == NULL)
        return NULL;

    while (((str[eko->i] >= 'A' && str[eko->i] <= 'Z')
            || (str[eko->i] >= 'a' && str[eko->i] <= 'z'))
            && str[eko->i] != '\0')
    {
        variable_env[k] = str[eko->i];
        ++k;
        ++eko->i;
    }
    variable_env[k] = '\0';

    return variable_env;
}

int expand_variable(char *variable_env, t_echo *eko)
{
    char *name = getenv(variable_env);

    if (name == NULL)
        return -1;

    int k = 0;
    while (name[k])
    {
        eko->line[eko->j] = name[k];
        ++eko->j;
        ++k;
    }

    return 1;
}

int dollar_double(char *str, t_echo *eko)
{
    char *variable_env;
    int result;
    
    if (str[eko->i] != '$')
        return 0;
    if (str[eko->i] == '$' && str[eko->i + 1] == ' ')
        return 0;
    if (str[eko->i] == '$' && str[eko->i + 1] == '\0')
        return 0;
    if (str[eko->i] == '$' && str[eko->i + 1] == '"')
        return 0;
    if (str[eko->i] == '$' && str[eko->i + 1] == '?')
        return 0;
    ++eko->i;
    variable_env = extract_variable_name(str, eko);
    if (variable_env == NULL)
        return 0;

    result = expand_variable(variable_env, eko);
    free(variable_env);
    return result;
}



