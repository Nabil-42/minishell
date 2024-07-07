/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:43:34 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 21:35:14 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"

void	skip_redirection_target(char *str, int *i)
{
	while (str[*i] && is_redirection(str[*i]))
		(*i)++;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	while (str[*i] && str[*i] != ' ')
		(*i)++;
}

void	handle_quotes(char c, int *in_single_quotes, int *in_double_quotes)
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

void	add_part_to_result(t_general *g, int *result_size, char *str, int end)
{
	int		part_len;
	char	*part;

	part_len = end - g->split_start;
	part = malloc(part_len + 1);
	if (!part)
	{
		return ;
	}
	strncpy(part, str + g->split_start, part_len);
	part[part_len] = '\0';
	g->split_result[*result_size] = part;
	(*result_size)++;
}

void	split_str_bis(char *str, int *i, t_general *g, int *result_size)
{
	handle_quotes(str[*i], &g->split_in_single_quotes,
		&g->split_in_double_quotes);
	if (!g->split_in_single_quotes && !g->split_in_double_quotes
		&& is_redirection(str[*i]))
	{
		if (g->split_start < *i)
			add_part_to_result(g, result_size, str, *i);
		skip_redirection_target(str, &*i);
		g->split_start = *i;
		g->split_redirection_found = 1;
	}
	else if (!g->split_in_single_quotes && !g->split_in_double_quotes
		&& str[*i] == ' ' && g->split_redirection_found)
		(g->split_redirection_found = 0);
	else
		(g->split_redirection_found = 0);
	++*i;
}

char	**split_str(char *str, int *result_size, t_general *g)
{
	int	len;
	int	i;

	len = strlen(str);
	g->split_result = malloc(PATH_MAX * sizeof(char *));
	if (!g->split_result)
		return (NULL);
	g->split_in_single_quotes = 0;
	g->split_in_double_quotes = 0;
	g->split_redirection_found = 0;
	g->split_start = 0;
	i = 0;
	*result_size = 0;
	while (i < len)
		split_str_bis(str, &i, g, result_size);
	if (g->split_start < len)
		add_part_to_result(g, result_size, str, len);
	g->split_result[*result_size] = NULL;
	return (g->split_result);
}
