/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_delimiters_bis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:37:06 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 11:35:22 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

void	toggle_quotes(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '\'' && !(*in_double_quotes))
	{
		*in_single_quotes = !(*in_single_quotes);
	}
	else if (c == '\"' && !(*in_single_quotes))
	{
		*in_double_quotes = !(*in_double_quotes);
	}
}

int	count_delimiters(const char *str)
{
	int	len;
	int	in_single_quotes;
	int	in_double_quotes;
	int	delimiter_count;
	int	i;

	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	delimiter_count = 0;
	len = strlen(str);
	while (i < len)
	{
		toggle_quotes(str[i], &in_single_quotes, &in_double_quotes);
		if (!in_single_quotes && !in_double_quotes && is_redirection(str[i]))
		{
			delimiter_count++;
			if ((str[i] == '>' && str[i + 1] == '>')
				|| (str[i] == '<' && str[i + 1] == '<'))
				i++;
		}
		i++;
	}
	return (delimiter_count);
}
