/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:02:53 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 15:21:24 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"

int	verif_quote_2(char *str, int i, int *double_quote_count,
		int *single_quote_count)
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
		return (ft_fprintf(2, "minishell: %s: 3 command not found\n", str), 1);
	return (0);
}
char	*verif_quote_bis(char *str)
{
	int		double_quote_count;
	int		single_quote_count;
	int		i;
	int		j;
	char	*new_str;

	single_quote_count = 0;
	double_quote_count = 0;
	j = 0;
	i = 0;
	if (verif_quote_2(str, i, &double_quote_count, &single_quote_count))
		return (NULL);
	new_str = malloc(sizeof(char) * (strlen(str) + 1));
	if (!new_str)
		return (NULL);
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

char	*verif_quote(char *str)
{
	int		double_quote_count;
	int		single_quote_count;
	int		i;
	int		j;
	char	*new_str;

	single_quote_count = 0;
	double_quote_count = 0;
	j = 0;
	i = 0;
	if (verif_quote_2(str, i, &double_quote_count, &single_quote_count))
		return (NULL);
	new_str = malloc(sizeof(char) * (strlen(str) + 10));
	if (!new_str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			if (str[i] == ' ')
				++j;
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	check_redirection_2(int *expecting_command, int *i, char *str)
{
	*expecting_command = 0;
	while (str[*i] && !isspace(str[*i]) && !is_redirection(str[*i]))
		i++;
}
int	is_space(char *str, int *i)
{
	if (isspace(str[*i]))
	{
		++*i;
		return (1);
	}
	return (0);
}

int	is_space_bis(char *str)
{
	int	i;

	i = 0;
	while (!isspace(str[i]) && str[i])
	{
		++i;
		if (isspace(str[i]))
			return (1);
	}
	return (0);
}
int	check_redirections(char *str)
{
	int i;
	int expecting_command;

	i = 0;
	expecting_command = 0;
	while (str[i])
	{
		if (is_space(str, &i))
			continue ;
		if (is_redirection(str[i]))
		{
			if (expecting_command)
				return (ft_fprintf(2, "minishell: %s: 4 command not found\n",
						str));
			if (str[i] == '<' && str[i + 1] == '<')
				i += 2;
			else if (str[i] == '>' && str[i + 1] == '>')
				i += 2;
			else
				(i++);
			expecting_command = 1;
		}
		else
			(check_redirection_2(&expecting_command, &i, str));
	}
	if (expecting_command)
		return (ft_fprintf(2, "minishell: %s: 5 command not found\n", str));
	return (0);
}