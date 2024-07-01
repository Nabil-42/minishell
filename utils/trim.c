/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:04:32 by nabil             #+#    #+#             */
/*   Updated: 2024/07/01 17:37:25 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

char *trim_space(char *str) 
{
        char *new_start;
        char *new_str;
    
    if (str == NULL) {
        return NULL;
    }

    // Trouve le premier caractère dont la valeur ASCII est > 32
    new_start = str;
    while (*new_start && *new_start <= 32) 
    {
        new_start++;
    }

    // Alloue de la mémoire pour la nouvelle chaîne
    new_str = ft_strdup(new_start);
    if (new_str == NULL) 
    {
        return NULL;
    }

    // Libère la chaîne d'origine
    return new_str;
}