/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:09:46 by nabboud           #+#    #+#             */
/*   Updated: 2024/06/19 22:15:28 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../lib/libft/includes/libft.h"

void free_tokens(char **tokens, int num_tokens) 
{
	int i;
	
	i = 0;
	while(i < num_tokens)
	{
        	free(tokens[i]);
		++i;
    	}
    	free(tokens);
}

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;

    while (i < n && src[i] != '\0') 
    {
        dest[i] = src[i];
        i++;
    }

    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

char **split_str(char *str, int *result_size) 
{
    char **result = NULL;
    *result_size = 0;

    int len = strlen(str);
    int in_quotes = 0;
    int start = 0;
    int i = 0;

        while (i < len)
        {
            if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')) 
            {
                if (in_quotes == 1)
                in_quotes = 0;
            else if (in_quotes == 0)
                in_quotes = 1;
            } 
            else if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
            {
                if (in_quotes == 2)
                    in_quotes = 0;
                else if (in_quotes == 0)
                    in_quotes = 2;
            }

            if (!in_quotes && is_delimiter(str[i])) 
            {
                if (start < i) 
                {
                    int part_len = i - start;
                    char *part = malloc(part_len + 1);
                    ft_strncpy(part, str + start, part_len);
                    part[part_len] = '\0';
                    result = realloc(result, (*result_size + 1) * sizeof(char *));
                    result[*result_size] = part;
                    (*result_size)++;
                }
            start = i + 1;
            }
            i++;
        }
        
    if (start < len) {
        int part_len = len - start;
        char *part = malloc(part_len + 1);
        strncpy(part, str + start, part_len);
        part[part_len] = '\0';
        result = realloc(result, (*result_size + 1) * sizeof(char *));
        result[*result_size] = part;
        (*result_size)++;
    }

    return result;
}

// Fonction pour vérifier si deux caractères forment un délimiteur de redirection ">>" ou "<<"
int is_double_delimiter(char c1, char c2) {
    return ((c1 == '>' && c2 == '>') || (c1 == '<' && c2 == '<'));
}

char **split_delimiters(const char *str, int *result_size) {
    char **result = NULL;
    *result_size = 0;

    int len = strlen(str);
    int in_quotes = 0; // 0: pas de guillemets, 1: guillemets simples, 2: guillemets doubles

    for (int i = 0; i < len; i++) {
        if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')) {
            if (in_quotes == 1)
                in_quotes = 0;
            else if (in_quotes == 0)
                in_quotes = 1;
        } else if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\')) {
            if (in_quotes == 2)
                in_quotes = 0;
            else if (in_quotes == 0)
                in_quotes = 2;
        }

        if (!in_quotes && is_delimiter(str[i])) {
            // Vérifier si le délimiteur est suivi immédiatement par le même délimiteur pour détecter les doubles
            if (i + 1 < len && str[i] == '>' && str[i + 1] == '>') {
                // Délimiteur double ">>"
                result = realloc(result, (*result_size + 1) * sizeof(char *));
                result[*result_size] = malloc(3); // Allouer de la mémoire pour le délimiteur double et le caractère nul
                result[*result_size][0] = '>';
                result[*result_size][1] = '>';
                result[*result_size][2] = '\0';
                (*result_size)++;
                i++; // Avancer un caractère de plus pour sauter le deuxième délimiteur
            } else if (i + 1 < len && str[i] == '<' && str[i + 1] == '<') {
                // Délimiteur double "<<"
                result = realloc(result, (*result_size + 1) * sizeof(char *));
                result[*result_size] = malloc(3); // Allouer de la mémoire pour le délimiteur double et le caractère nul
                result[*result_size][0] = '<';
                result[*result_size][1] = '<';
                result[*result_size][2] = '\0';
                (*result_size)++;
                i++; // Avancer un caractère de plus pour sauter le deuxième délimiteur
            } else {
                // Délimiteur simple
                result = realloc(result, (*result_size + 1) * sizeof(char *));
                result[*result_size] = malloc(2); // Allouer de la mémoire pour le délimiteur et le caractère nul
                result[*result_size][0] = str[i];
                result[*result_size][1] = '\0';
                (*result_size)++;
            }
        }
    }

    return result;
}
