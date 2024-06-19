/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:16:27 by nabil             #+#    #+#             */
/*   Updated: 2024/06/19 14:41:31 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "../includes/minishell.h"
#include "env/env.h"

int is_number(const char *str)
{
    if (*str == '+' || *str == '-') 
        str++;
    while (*str) 
    {
        if (!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

void ft_exit(char **tab, t_general *g)
{
        int exit_code;
        
        if (tab[1] == NULL)
                exit(g->$);
        if (tab[2] != NULL) 
        {
                ft_fprintf(2, "exit: trop d'arguments\n");
                return;
        }
        if (!is_number(tab[1])) 
        {
                ft_fprintf(2, "exit: %s: argument numérique nécessaire\n", tab[1]);
                exit(2);
        }
        exit_code = atoi(tab[1]);
        exit(exit_code % 256);
}