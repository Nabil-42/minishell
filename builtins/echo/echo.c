/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/19 11:47:51 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

#define PATH_MAX 4096

char *remake_str(char **tab, t_echo *eko, int i)
{
        int j;
        int k;
        char *new_str;
        
        if (tab[i] == NULL)
                return (NULL);
        new_str = malloc(sizeof(char) * eko->len_str + 1);
        if (new_str == NULL)
                return (NULL);
        k = 0;            
        while (tab[i])
        {
                j = 0;
                while(tab[i][j])
                {
                        new_str[k] = tab[i][j];
                        ++k, ++j;
                }
                if (tab[i + 1] != NULL)
                        new_str[k] = ' ';
                ++k, ++i;
        }
        k--;
        new_str[k] = '\0';
        return(new_str);
}


void    echo_2(char **tab, char *str, t_echo *eko, char *tmp)
{
    if (tab[1] && ft_strcmp(tab[1], "-n") == 0) 
    {
        echo_args(str, eko, tab, tmp);
        free(eko->line);
        free(str);
        return;
    }
    if (*tmp == '\0' && str[0] != 39 && str[1] != 39) 
    {
        dollar(str, eko);
        free_tab(tab);
        free(eko->line);
        free(str);
        return;
    }
    printf("%s\n", tmp);
    free_tab(tab);
    free(eko->line);
    free(str);
}

void echo(char **tab, t_echo *eko)
{
    char *str = NULL;
    char *tmp = NULL;

    if (tab[1] && ft_strcmp(tab[1], "-n") == 0)
                str = remake_str(tab, eko, 2);
        else (str = remake_str(tab, eko, 1));
    if (!str) 
    {
        free_tab(tab);
        free(str);
        return;
    }
    eko->line = malloc(sizeof(char) * (eko->len_str + PATH_MAX + 1));
    if (!eko->line) 
        return (free(str), (void)0);
    tmp = echo_verif_quote(str, eko);
    if (tmp == NULL)
    {
        free(eko->line);
        free(str); 
        return;
    }
    echo_2(tab, str, eko, tmp);
}
