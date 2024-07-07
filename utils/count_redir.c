/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:37:06 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 11:13:37 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

int	update_count_and_index(int count, int *i, int redirection_type)
{
	if (redirection_type > 0)
	{
		count += redirection_type;
		if (redirection_type == 2)
			(*i)++;
	}
	return (count);
}

void	update_quote_state(char ch, int *in_single_quotes,
		int *in_double_quotes)
{
	if (ch == '\'')
	{
		if (*in_single_quotes)
			*in_single_quotes = 0;
		else if (!*in_double_quotes)
			*in_single_quotes = 1;
	}
	else if (ch == '"')
	{
		if (*in_double_quotes)
			*in_double_quotes = 0;
		else if (!*in_single_quotes)
			*in_double_quotes = 1;
	}
}

int	is_redirection_bis(char *str, int index)
{
	if (str[index] == '<' || str[index] == '>')
	{
		if (str[index] == '<' && str[index + 1] == '<')
			return (2);
		else if (str[index] == '>' && str[index + 1] == '>')
			return (2);
		else
			return (1);
	}
	return (0);
}

int	count_redirections(char *str)
{
	int	count;
	int	i;
	int	in_single_quotes;
	int	in_double_quotes;
	int	redirection_type;

	count = 0;
	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (str[i] != '\0')
	{
		update_quote_state(str[i], &in_single_quotes, &in_double_quotes);
		if (!in_single_quotes && !in_double_quotes)
		{
			redirection_type = is_redirection_bis(str, i);
			count = update_count_and_index(count, &i, redirection_type);
		}
		i++;
	}
	return (count);
}
