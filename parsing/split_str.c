/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:43:34 by nabil             #+#    #+#             */
/*   Updated: 2024/07/01 16:56:08 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"



void skip_redirection_target(char *str, int *i)
{
	// Skip the redirection symbol
	while (str[*i] && is_redirection(str[*i]))
		(*i)++;
	// Skip spaces
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	// Skip until the next space or end of string
	while (str[*i] && str[*i] != ' ')
		(*i)++;
}

void handle_quotes(char c, int *in_single_quotes, int *in_double_quotes)
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

void add_part_to_result(char **result, int *result_size, char *str, int start, int end)
{
	int part_len = end - start;
	char *part = malloc(part_len + 1);
	if (!part)
	{
		return;
	}
	strncpy(part, str + start, part_len);
	part[part_len] = '\0';
	result[*result_size] = part;
	(*result_size)++;
}

char **split_str(char *str, int *result_size)
{
	char **result = malloc(PATH_MAX * sizeof(char *));
	int len = strlen(str);
	int in_single_quotes = 0, in_double_quotes = 0;
	int start = 0, i = 0;
	int redirection_found = 0;

	*result_size = 0;
	if (!result)
	{
		return NULL;
	}

	while (i < len)
	{
		handle_quotes(str[i], &in_single_quotes, &in_double_quotes);

		if (!in_single_quotes && !in_double_quotes && is_redirection(str[i]))
		{
			// Add the previous part if it exists
			if (start < i)
			{
				add_part_to_result(result, result_size, str, start, i);
			}
			// Skip the redirection target
			skip_redirection_target(str, &i);
			start = i;
			redirection_found = 1;
		}
		else if (!in_single_quotes && !in_double_quotes && str[i] == ' ' && redirection_found)
		{
			redirection_found = 0;
		}
		else
		{
			redirection_found = 0;
		}
		i++;
	}

	// Add the last part if it exists
	if (start < len)
	{
		add_part_to_result(result, result_size, str, start, len);
	}
	result[*result_size] = NULL;
	return result;
}
