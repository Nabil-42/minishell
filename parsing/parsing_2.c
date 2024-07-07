/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:02:53 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 20:43:31 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"

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
	return (new_str[j] = '\0', new_str);
}

void	verif_quote_rest(char *str, int i, int *j, char *new_str)
{
	if (str[i] != '"' && str[i] != '\'')
	{
		if (str[i] == ' ')
			++*j;
		new_str[*j] = str[i];
		++*j;
	}
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
		verif_quote_rest(str, i, &j, new_str);
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	check_redir_bis(char *str, int *i)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
		*i += 2;
	else if (str[*i] == '>' && str[*i + 1] == '>')
		*i += 2;
	else
		(++*i);
}

int	check_redirections(char *str)
{
	int	i;
	int	expecting_command;

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
			check_redir_bis(str, &i);
			expecting_command = 1;
		}
		else
			(check_redirection_2(&expecting_command, &i, str));
	}
	if (expecting_command)
		return (ft_fprintf(2, "minishell: %s: 5 command not found\n", str));
	return (0);
}
