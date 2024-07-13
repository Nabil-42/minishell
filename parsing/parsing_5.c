/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:02:53 by nabil             #+#    #+#             */
/*   Updated: 2024/07/13 11:20:31 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"

void	multiple_pipe(char *line, t_general *g)
{
	char	*new_line;

	new_line = verif_quote(line);
	if (new_line == NULL || *new_line == '\0')
		return (free(new_line));
	check_redirections(new_line);
	check_special_characters(new_line);
	count_commands(new_line, g);
	free(g->line);
	g->line = new_line;
}

char *vide_quote(char **tab)
{
	int i;
	int j;
	char *str = NULL;
	char *new_str;

	str = remake_str_bis(tab);
	if (!str)
	{
		return NULL;
	}
	new_str = malloc(sizeof(char) * (strlen(str) + 1));
	if (!new_str)
		return (free(str), NULL);	
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == '"' || str[i] == 39)
			++i;
		if (str[i] == '\0')
			break;
		new_str[j] = str[i];
		++i;
		++j;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}
