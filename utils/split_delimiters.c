/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_delimiters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:37:06 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 11:34:34 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

int	is_redirection_tris(char c)
{
	return (c == '<' || c == '>');
}

char	*allocate_delimiter(const char *str, int *i)
{
	char	*delimiter;

	if ((str[*i] == '>' && str[*i + 1] == '>')
		|| (str[*i] == '<' && str[*i + 1] == '<'))
	{
		delimiter = malloc(3);
		delimiter[0] = str[*i];
		delimiter[1] = str[*i + 1];
		delimiter[2] = '\0';
		(*i)++;
	}
	else
	{
		delimiter = malloc(2);
		delimiter[0] = str[*i];
		delimiter[1] = '\0';
	}
	return (delimiter);
}

char	**initialize_result(int delimiter_count)
{
	char	**result;

	result = malloc((delimiter_count + 1) * sizeof(char *));
	if (!result)
	{
		return (NULL);
	}
	return (result);
}

void	process_string(const char *str, char **result, int *result_size)
{
	int	len;
	int	in_single_quotes;
	int	i;
	int	in_double_quotes;

	len = strlen(str);
	in_single_quotes = 0;
	in_double_quotes = 0;
	i = 0;
	while (i < len)
	{
		toggle_quotes(str[i], &in_single_quotes, &in_double_quotes);
		if (!in_single_quotes && !in_double_quotes
			&& is_redirection_tris(str[i]))
		{
			result[*result_size] = allocate_delimiter(str, &i);
			if (!result[*result_size])
				return (free_tab(result), result = NULL, (void)0);
			(*result_size)++;
		}
		i++;
	}
	result[*result_size] = NULL;
}

char	**split_delimiters(const char *str, int *result_size)
{
	int		delimiter_count;
	char	**result;

	delimiter_count = count_delimiters(str);
	result = initialize_result(delimiter_count);
	if (!result)
	{
		return (NULL);
	}
	*result_size = 0;
	process_string(str, result, result_size);
	if (!result)
	{
		return (NULL);
	}
	return (result);
}
