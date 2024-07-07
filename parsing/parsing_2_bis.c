/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:02:53 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 20:45:07 by nabboud          ###   ########.fr       */
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
