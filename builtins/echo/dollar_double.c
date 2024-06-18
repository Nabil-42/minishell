/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/18 22:38:31 by nabil            ###   ########.fr       */
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
    if (str[eko->i] != '$')
        return 0;

    ++eko->i;
    char *variable_env = extract_variable_name(str, eko);

    if (variable_env == NULL)
        return 0;

    int result = expand_variable(variable_env, eko);

    free(variable_env);
    return result;
}



