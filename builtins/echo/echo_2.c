/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:07:16 by nabil             #+#    #+#             */
/*   Updated: 2024/06/18 23:27:05 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

int echo_verif_1(t_echo *eko, char *str, int *i)
{
                eko->flag_i = 0;
                eko->flag = 0;
                if ((str[*i] == '"'))
                {
                        while (str[*i])
                        {
                                ++*i;
                                if (str[*i] == '"')
                                        {
                                                echo_take_of_double_quote(str, eko, *i);
                                                ++*i;
                                                eko->flag_i = 1;
                                                eko->dir = *i;
												eko->flag = 1;
										}
                                if (eko->flag == 1)
                                        break;
                        }
						if (eko->flag == 1)
                                return (2);
                        return (printf("minishell: %s: command not found\n", str), 1);                           
                }
                return (0);
}
int echo_verif_2(t_echo *eko, char *str, int *i)
{
                eko->flag = 0;
                if (str[*i] == 39)
                {
                        while (str[*i])
                        {
                                ++*i;
                                if (str[*i] == 39)
                                        {
                                                echo_take_of_simple_quote(str, eko, *i);
                                                ++*i;
                                                eko->flag = 1;
                                                eko->dir = *i;
                                        }
                                if (eko->flag == 1)
                                        break;
                        }
                        if (eko->flag == 1)
                                return (2);
                      	return (printf("minishell: %s: command not found\n", str), 1);
                }
                return (0);
}

void echo_verif_3(t_echo *eko, int *i, char *str)
{ 
    if (eko->dir != *i)
        {
                while (str[eko->dir] && (str[eko->dir] != '<' && str[eko->dir] != '>'))
                {

                        eko->line[eko->j] = str[eko->dir];
                        eko->j++;
                        eko->dir++;
                }
                eko->line[eko->j] = '\0';
        }
}

char *echo_verif_quote(char *str, t_echo *eko)
{
        int i;
        
        eko->line[0] = '\0';
        i = 0;
        while (str[i])
        {
            if (echo_verif_1(eko, str, &i) == 2)
                continue;
            else if (echo_verif_1(eko, str, &i) == 1)
                return (NULL);
            if (echo_verif_2(eko, str, &i) == 2)
                continue;
            else if (echo_verif_2(eko, str, &i) == 1)
                return (NULL);
            if (eko->flag_i == 0)
                ++i;
        }
        if (eko->line[0] == '\0')
                return (eko->line);
        echo_verif_3(eko, &i, str);
        if ((str[eko->dir] == '>' && str[eko->dir + 1] == '>')
            || (str[eko->dir] == '<' && str[eko->dir + 1] == '<'))
                return (direction_double(str, eko->dir, eko), (NULL));
        if (str[eko->dir] == '>' || str[eko->dir] == '<')
                return (direction(str, eko->dir, eko), (NULL));
        return (eko->line);
}

void echo_args(char *str, t_echo *eko, char **tab, char *tmp)
{
        if (tmp[0] == '\0')
        {
                dollar_n(str, eko);
                free_tab(tab);
                return;
        }
        printf("%s", tmp);
        free_tab(tab);
}




