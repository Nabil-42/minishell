/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:07:44 by nabil             #+#    #+#             */
/*   Updated: 2024/06/23 09:27:07 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"

int	is_redirection(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	check_special_characters(const char *str)
{
	while (*str != '\0')
	{
		if (*str == ';' || *str == '\\' || *str == '&' || *str == '('
			|| *str == ')')
		{
			return (printf("minishell: %s: 8 command not found\n", str));
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

int	count_pipe(char *str)
{
	int	count;
	int	i;
	int	inside_token;

	count = 0;
	i = 0;
	inside_token = 0;
	int in_single_quotes = 0;
	int in_double_quotes = 0;
	while (str[i] != '\0')
	{
		// Gérer les guillemets simples
		if (str[i] == '\'')
		{
			if (in_single_quotes)
			{
				in_single_quotes = 0;
			}
			else if (!in_double_quotes)
			{
				in_single_quotes = 1;
			}
			// Gérer les guillemets doubles
		}
		else if (str[i] == '"')
		{
			if (in_double_quotes)
			{
				in_double_quotes = 0;
			}
			else if (!in_single_quotes)
			{
				in_double_quotes = 1;
			}
		}
		// Compter les tokens seulement si on n'est pas dans des guillemets
		if (!in_single_quotes && !in_double_quotes)
		{
			if (is_delimiter_pipe(str[i]))
			{
				// Vérifier pour les délimiteurs doubles
				if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<'
						&& str[i + 1] == '<'))
				{
					count++;
					i++; // Sauter le deuxième caractère du délimiteur double
				}
				else
				{
					count++;
				}
				inside_token = 0;
			}
			else
			{
				if (!inside_token)
				{
					count++;
					inside_token = 1;
				}
			}
		}
		i++;
	}
	return (count);
}
