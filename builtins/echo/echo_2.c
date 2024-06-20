/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:07:16 by nabil             #+#    #+#             */
/*   Updated: 2024/06/20 08:37:25 by nabil            ###   ########.fr       */
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

void echo_verif_3(t_echo *eko, t_general *g)
{ 
        int i;

        i = 0;
        if (g->tab_dir[i] == NULL)
                return;
        printf("%s\n", g->tab_dir[i]);
        while (g->tab_dir[i] != NULL && g->tab_dir[i][0] != '|')
        {
                if (g->tab_dir[i] != NULL && g->tab_dir[i][0] == '>')
                        direction(g->tab_cmd[i + 1], eko, g);
                if (g->tab_dir[i] != NULL && g->tab_dir[i][0] == '>'
                        && g->tab_dir[i] != NULL && g->tab_dir[i][1] == '>')
                        direction_double(g->tab_cmd[i + 1], eko, g);
                eko->check_dir = 1;
                ++i;
        }
}

char *echo_verif_quote(char *str, t_echo *eko, t_general *g)
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
        echo_verif_3(eko, g);
        if (eko->check_dir == 1)
                return (NULL);
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




