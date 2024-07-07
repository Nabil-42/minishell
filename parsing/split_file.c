/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:14:24 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 21:11:06 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
	{
		(*i)++;
	}
}

char	*get_next_token(char *str, int *i)
{
	int		quote;
	int		start;
	int		len;
	char	*token;

	quote = 0;
	start = *i;
	while (str[*i] && (str[*i] != ' ' || quote % 2 != 0))
	{
		if (str[*i] == '"')
			quote += 1;
		(*i)++;
	}
	len = *i - start;
	token = malloc(len + 1);
	if (!token)
	{
		return (NULL);
	}
	strncpy(token, str + start, len);
	token[len] = '\0';
	return (token);
}

void	handle_quotes_file(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '\'' && !(*in_double_quotes))
	{
		*in_single_quotes = !(*in_single_quotes);
	}
	else if (c == '"' && !(*in_single_quotes))
	{
		*in_double_quotes = !(*in_double_quotes);
	}
}

void	split_file_bis(char *str, int *i, char **result, int *result_size)
{
	char	*token;

	while (str[*i] && is_redirection(str[*i]))
		++*i;
	skip_spaces(str, i);
	if (str[*i] && str[*i] != ' ')
	{
		token = get_next_token(str, i);
		if (token)
		{
			result[*result_size] = token;
			(*result_size)++;
		}
	}
}

char	**split_file(char *str, int *result_size)
{
	char	**result;
	int		len;
	int		in_single_quotes;
	int		in_double_quotes;
	int		i;

	i = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	len = strlen(str);
	result = malloc(PATH_MAX * sizeof(char *));
	*result_size = 0;
	if (!result)
		return (NULL);
	while (i < len)
	{
		handle_quotes_file(str[i], &in_single_quotes, &in_double_quotes);
		if (!in_single_quotes && !in_double_quotes && is_redirection(str[i]))
			split_file_bis(str, &i, result, result_size);
		else
			(i++);
	}
	result[*result_size] = NULL;
	return (result);
}
