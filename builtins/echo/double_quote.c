/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/14 11:49:33 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

#define PATH_MAX 4096

int dollar_n(char *str, t_echo *eko)
{
    char *variable_env;
    int i = 0;
    int j = 0;
    int k = 0;
    char *name;

    while (str[i])
    {
        if (str[i] == '$')
        {
            variable_env = malloc(PATH_MAX + 1);
            if (variable_env == NULL)
                return 0;
            ++i;
            k = 0;
            while (((str[i] >= 'A' && str[i] <= 'Z')
                    || (str[i] >= 'a' && str[i] <= 'z'))
                    && str[i] != '\0')
            {
                variable_env[k] = str[i];
                ++k;
                ++i;
            }
            variable_env[k] = '\0';
            name = getenv(variable_env);
            k = 0;
            if (name == NULL)
                return 0;
            while (name[k])
            {
                eko->line[j] = name[k];
                ++j;
                ++k;
            }
            free(variable_env);
        }
        eko->line[j] = str[i];
        ++i;
        ++j;
    }
    eko->line[j] = '\0';
    printf("%s", eko->line);
    return 0;
}

int dollar(char *str, t_echo *eko)
{
    char *variable_env;
    int i = 0;
    int j = 0;
    int k = 0;
    char *name;

    while (str[i])
    {
        if ((str[i] == '>' && str[i + 1] == '>')
            || (str[i] == '<' && str[i + 1] == '<'))
        {
                eko->line[j] = '\0';
                direction_double(str, i, eko);
                return (0);
        }
        if (str[i] == '>' || str[i] == '<')
        {
                eko->line[j] = '\0';
                direction(str, i, eko);
                return (0);
        }
            
        if (str[i] == '$')
        {
            variable_env = malloc(PATH_MAX + 1);
            if (variable_env == NULL)
                return 0;
            ++i;
            k = 0;
            while (((str[i] >= 'A' && str[i] <= 'Z')
                    || (str[i] >= 'a' && str[i] <= 'z'))
                    && str[i] != '\0')
            {
                variable_env[k] = str[i];
                ++k;
                ++i;
            }
            variable_env[k] = '\0';
            name = getenv(variable_env);
            free(variable_env);
            if (name == NULL)
                return 0;
            k = 0;
            if (name == NULL)
                return 0;
            while (name[k])
            {
                eko->line[j] = name[k];
                ++j;
                ++k;
            }
            
        }
        eko->line[j] = str[i];
        ++i;
        ++j;
    }
    eko->line[j] = '\0';
    printf("%s\n", eko->line);
    return 0;
}

int dollar_double(char *str, t_echo *eko)
{
    char *variable_env;
    int k = 0;
    char *name;

    if (str[eko->i] != '$')
        return 0;
    variable_env = malloc(PATH_MAX + 1);
    if (variable_env == NULL)
        return 0;
    if (str[eko->i] == '$')
    {
        ++eko->i;
        k = 0;
        while (((str[eko->i] >= 'A' && str[eko->i] <= 'Z')
                || (str[eko->i] >= 'a' && str[eko->i] <= 'z'))
                && str[eko->i] != '\0')
        {
            variable_env[k] = str[eko->i];
            ++k;
            ++eko->i;
        }
        variable_env[k] = '\0';
        name = getenv(variable_env);
        free(variable_env); 
        if (name == NULL)
            return -1;
        k = 0;
        while (name[k])
        {
            eko->line[eko->j] = name[k];
            ++eko->j;
            ++k;
        }
        return 1; 
    }
    return 0; 
}




int echo_take_of_double_quote(char *str, t_echo *eko, int n)
{
	int flag;
        int dollar_check;
        flag = 0;
        while(eko->i <= n)
        {
                if (str[eko->i] == '"' && str[eko->i + 1] == '"')
                {
                        eko->line[eko->j] = '\0';
                        eko->i += 2;
                        return (2);
                }
                
                if (str[eko->i] == '"')
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
                dollar_check = dollar_double(str, eko);
                if (dollar_check == -1)
                        return (-1);
                if (dollar_check > 0)
                        continue;
                eko->line[eko->j] = str[eko->i];
                ++eko->i;
                ++eko->j;
        }
        return (0);
}