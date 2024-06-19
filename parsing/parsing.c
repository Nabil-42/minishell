/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:09:46 by nabboud           #+#    #+#             */
/*   Updated: 2024/06/19 11:17:10 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../lib/libft/includes/libft.h"

int verif_quote_2(char *str, int i, int *double_quote_count, int *single_quote_count)
{
    while (str[i]) 
    {
        if (str[i] == '"') 
            (*double_quote_count)++;
        else if (str[i] == '\'') 
            (*single_quote_count)++;
        i++;
    }
    if (*double_quote_count % 2 != 0 || *single_quote_count % 2 != 0)
        return (printf("minishell: %s: command not found\n", str), 1);
    return (0);
}

char *verif_quote(char *str) 
{
    int double_quote_count;
    int single_quote_count;
    int i;
    int j;
    char *new_str;
    
    single_quote_count = 0;
    double_quote_count = 0;
    j = 0;
    i = 0;
    if (verif_quote_2(str, i, &double_quote_count, &single_quote_count))
            return(NULL);
    new_str = malloc(sizeof(char) * (strlen(str) + 1));
    if (!new_str)
        return NULL;
    while (str[i]) 
    {
        if (str[i] != '"' && str[i] != '\'') 
        {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0'; 
    return (new_str);
}



int is_redirection(char c) 
{
	if (c == '<' || c == '>' || c == '|')
    		return 1;
	return 0;
}

void check_redirection_2(int *expecting_command, int *i, char *str)
{
    *expecting_command = 0;
    while (str[*i] && !isspace(str[*i]) && !is_redirection(str[*i]))
            i++;
}
int is_space(char *str, int *i)
{
    if (isspace(str[*i])) 
	    {
            ++*i;
            return (1);
        }
    return (0);
}
int check_redirections(char *str) 
{
    int i;
    int expecting_command;

    i = 0;
    expecting_command = 0;
    while (str[i]) 
    {
        if (is_space(str, &i))
            continue;
        if (is_redirection(str[i])) 
        {
            if (expecting_command)
                return (printf("minishell: %s: command not found\n", str));
            if (str[i] == '<' && str[i + 1] == '<') 
                i += 2;
            else if (str[i] == '>' && str[i + 1] == '>') 
                i += 2;
             else (i++);
            expecting_command = 1;
        } 
        else (check_redirection_2(&expecting_command, &i, str));
    }
    if (expecting_command)
        return (printf("minishell: %s: command not found\n", str));
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

int is_delimiter(char c) 
{
    return (c == '|' || c == '<' || c == '>');
}

int count_tokens(char *str) 
{
    int count;
    int i;
    int inside_token;

    count = 0;
    i = 0;
    inside_token = 0;
    while (str[i] != '\0') 
    {
        if (is_delimiter(str[i]))
            inside_token = 0;
        else 
        {
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

char **split_str(char *str, int *num_tokens) 
{
    char **tokens = NULL;
    int max_tokens = count_tokens(str);
    int token_count = 0;
    int i = 0;
    int start = 0;
    int token_length;

    tokens = malloc(max_tokens * sizeof(char *));
    if (tokens == NULL)
        (perror("Allocation error"), exit(EXIT_FAILURE));
    while (str[i] != '\0') 
    {    
        while (str[i] != '\0' && is_delimiter(str[i]))
                i++; 
        start = i;
        while (str[i] != '\0' && !is_delimiter(str[i]))
                i++;
        token_length = i - start;
        if (token_length > 0) 
        {
            tokens[token_count] = malloc((token_length + 1) * sizeof(char));
            if (tokens[token_count] == NULL)
                (perror("Allocation error"), exit(EXIT_FAILURE));
            ft_strncpy(tokens[token_count], &str[start], token_length);
            tokens[token_count][token_length] = '\0';
            token_count++;
        }
    }
    *num_tokens = token_count;
    return tokens;
}

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
