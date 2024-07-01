/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:09:46 by nabboud           #+#    #+#             */
/*   Updated: 2024/07/01 17:12:39 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"

void	free_tokens(char **tokens, int num_tokens)
{
	int	i;

	i = 0;
	while (i < num_tokens)
	{
		free(tokens[i]);
		++i;
	}
	free(tokens);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int is_redirection(char c) 
{
	if (c == '<' || c == '>')
    		return 1;
	return 0;
}

// char **split_delimiters(const char *str, int *result_size) 
// {
//     int len = strlen(str);
//     int in_single_quotes = 0;
//     int in_double_quotes = 0;
//     int delimiter_count = 0;

//     int i = 0;
//     while (i < len) 
// 	{
//         if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')) 
// 		{
//             in_single_quotes = !in_single_quotes;
//         } else if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\')) {
//             in_double_quotes = !in_double_quotes;
//         }

//         if (!in_single_quotes && !in_double_quotes && is_redirection(str[i])) {
//             delimiter_count++;
//             if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')) {
//                 i++;
//             }
//         }
//         i++;
//     }

//     char **result = malloc((delimiter_count + 1) * sizeof(char *));
//     if (!result) {
//         return NULL;
//     }
//     *result_size = 0;

//     i = 0;
//     while (i < len) 
// 	{
//         if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')) 
// 		{
//             in_single_quotes = !in_single_quotes;
//         } else if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\')) 
// 		{
//             in_double_quotes = !in_double_quotes;
//         }

//         if (!in_single_quotes && !in_double_quotes && is_redirection(str[i])) {
//             if (i + 1 < len && str[i] == '>' && str[i + 1] == '>') {
//                 result[*result_size] = malloc(3);
//                 if (!result[*result_size]) {
//                     free_tab(result);
//                     return NULL;
//                 }
//                 result[*result_size][0] = '>';
//                 result[*result_size][1] = '>';
//                 result[*result_size][2] = '\0';
//                 (*result_size)++;
//                 i++;
//             } else if (i + 1 < len && str[i] == '<' && str[i + 1] == '<') {
//                 result[*result_size] = malloc(3);
//                 if (!result[*result_size]) {
//                     free_tab(result);
//                     return NULL;
//                 }
//                 result[*result_size][0] = '<';
//                 result[*result_size][1] = '<';
//                 result[*result_size][2] = '\0';
//                 (*result_size)++;
//                 i++;
//             } else {
//                 result[*result_size] = malloc(2);
//                 if (!result[*result_size]) {
//                     free_tab(result);
//                     return NULL;
//                 }
//                 result[*result_size][0] = str[i];
//                 result[*result_size][1] = '\0';
//                 (*result_size)++;
//             }
//         }
//         i++;
//     }
//     result[*result_size] = NULL;
//     return result;
// }