/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:09:46 by nabboud           #+#    #+#             */
/*   Updated: 2024/06/15 16:40:52 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../lib/libft/includes/libft.h"

char *verif_quote(char *str) 
{
    int double_quote_count = 0;
    int single_quote_count = 0;
    int i = 0;
    int j = 0;
    char *new_str;

    // Compter le nombre de doubles quotes et de simples quotes
    while (str[i]) {
        if (str[i] == '"') {
            double_quote_count++;
        } else if (str[i] == '\'') {
            single_quote_count++;
        }
        i++;
    }

    // Vérifier si le nombre de quotes est pair
    if (double_quote_count % 2 != 0 || single_quote_count % 2 != 0) {
        return (printf("minishell: %s: command not found\n", str), NULL);
    }

    // Allouer de la mémoire pour la nouvelle chaîne
    new_str = malloc(sizeof(char) * (strlen(str) + 1));
    if (!new_str) {
        return NULL;
    }

    // Réinitialiser l'indice
    i = 0;

    while (str[i]) {
        if (str[i] != '"' && str[i] != '\'') {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0'; 

    return new_str;
}

int is_redirection(char c) 
{
	if (c == '<' || c == '>' || c == '|')
    		return 1;
	return 0;
}

int check_redirections(char *str) 
{
    int i = 0;
    int expecting_command = 0; // Flag to check if we are expecting a command or filename

    while (str[i]) 
    {
        // Skip whitespace
        if (isspace(str[i])) 
	{
            i++;
            continue;
        }

        // Check for redirections
        if (is_redirection(str[i])) 
	{
            if (expecting_command)
	    {
                return (printf("minishell: %s: command not found\n", str)); // Error: Two consecutive redirections or missing command/filename
            }

            // Handle '<<' and '>>'
            if (str[i] == '<' && str[i + 1] == '<') {
                i += 2;
            } else if (str[i] == '>' && str[i + 1] == '>') {
                i += 2;
            } else {
                i++;
            }

            expecting_command = 1; // After a redirection, we expect a command or filename
        } else {
            // We have a command or filename, reset the flag
            expecting_command = 0;
            while (str[i] && !isspace(str[i]) && !is_redirection(str[i])) {
                i++;
            }
        }
    }

    // If we end the string expecting a command or filename, it's an error
    if (expecting_command) {
        return (printf("minishell: %s: command not found\n", str));
    }

    return 0; // No errors found
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
    g->count = 0; // On commence avec une commande, car au moins une commande est toujours présente

    // Parcourir la chaîne caractère par caractère
    for (int i = 0; command_line[i] != '\0'; ++i) {
        if (command_line[i] == '|') {
            g->count++;
        }
    }
}

int is_delimiter(char c) 
{
    return (c == '|' || c == '<' || c == '>');
}

int count_tokens(char *str) 
{
    int count = 0;
    int i = 0;
    int inside_token = 0;

    while (str[i] != '\0') {
        if (is_delimiter(str[i]))
	{
            inside_token = 0;
        } 
	else {
            if (!inside_token) 
	    {
                count++;
                inside_token = 1;
            }
        }
        i++;
    }

    return count;
}

char *ft_strncpy(char *dest, const char *src, size_t n) {
    size_t i = 0;

    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    while (i < n) {
        dest[i] = '\0';
        i++;
    }

    return dest;
}


// Fonction pour découper la chaîne en tokens
char **split_str(char *str, int *num_tokens) 
{
    char **tokens = NULL;
    int max_tokens = count_tokens(str);  // Calculer le nombre maximum de tokens
    int token_count = 0;
    int i = 0;
    int start = 0;

    tokens = malloc(max_tokens * sizeof(char *));
    if (tokens == NULL) {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    while (str[i] != '\0') {
        // Trouver le début du prochain token
        while (str[i] != '\0' && is_delimiter(str[i])) {
            i++;  // Ignorer les délimiteurs au début de la chaîne
        }
        start = i;

        // Trouver la fin du token
        while (str[i] != '\0' && !is_delimiter(str[i])) {
            i++;
        }

        // Extraire le token
        int token_length = i - start;
        if (token_length > 0) {
            tokens[token_count] = malloc((token_length + 1) * sizeof(char));
            if (tokens[token_count] == NULL) {
                perror("Allocation error");
                exit(EXIT_FAILURE);
            }
            ft_strncpy(tokens[token_count], &str[start], token_length);
            tokens[token_count][token_length] = '\0';
            token_count++;
        }
    }

    // Mettre à jour le nombre de tokens
    *num_tokens = token_count;

    return tokens;
}

// Fonction pour libérer la mémoire allouée pour les tokens
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

