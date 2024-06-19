/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:07:44 by nabil             #+#    #+#             */
/*   Updated: 2024/06/19 21:08:13 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../lib/libft/includes/libft.h"

int is_redirection(char c) 
{
	if (c == '<' || c == '>' || c == '|')
    		return 1;
	return 0;
}

int check_special_characters(const char *str)
 {
    while (*str != '\0') {
        if (*str == ';' || *str == '\\' || *str == '&' || *str == '(' || *str == ')') {
            return (printf("minishell: %s: command not found\n", str));
        }
        str++;
    }
    return (0);
}

void count_commands(char *command_line, t_general *g) 
{
    g->count = 0; 
    int i;
    
    i = 0;
    while (command_line[i] != '\0')
    {
        if (command_line[i] == '|')
            g->count++;
        ++i;
    }
}
