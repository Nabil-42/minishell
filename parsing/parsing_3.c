/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:07:44 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 20:52:01 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"

int	check_special_characters(const char *str)
{
	while (*str != '\0')
	{
		if (*str == ';' || *str == '\\' || *str == '&' || *str == '('
			|| *str == ')')
		{
			return (ft_fprintf(2, "minishell: %s: 6 command not found\n", str));
		}
		str++;
	}
	return (0);
}

void	count_commands(char *command_line, t_general *g)
{
	int	i;

	g->count = 0;
	i = 0;
	while (command_line[i] != '\0')
	{
		if (command_line[i] == '|')
			g->count++;
		++i;
	}
}

int	is_delimiter_pipe(char c)
{
	return (c == '|');
}

int	count_pipe_bis(char *str, int i, int *in_single_quotes,
		int *in_double_quotes)
{
	int	count;

	count = 0;
	if (str[i] == '\'')
	{
		if (*in_single_quotes)
			*in_single_quotes = 0;
		else if (!*in_single_quotes)
			*in_single_quotes = 1;
	}
	else if (str[i] == '"')
	{
		if (*in_double_quotes)
			*in_double_quotes = 0;
		else if (!*in_single_quotes)
			*in_double_quotes = 1;
	}
	else if (!*in_single_quotes && !*in_double_quotes)
	{
		if (is_delimiter_pipe(str[i]))
			count++;
	}
	return (count);
}

int	count_pipe(char *str)
{
	int	count;
	int	i;
	int	in_single_quotes;
	int	in_double_quotes;

	count = 0;
	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (str[i] != '\0')
	{
		count += count_pipe_bis(str, i, &in_single_quotes, &in_double_quotes);
		i++;
	}
	return (count);
}
