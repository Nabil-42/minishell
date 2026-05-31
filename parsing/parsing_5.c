/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:02:53 by nabil             #+#    #+#             */
/*   Updated: 2024/08/08 11:58:36 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"

char	**cmd_args(char *line)
{
	char	**tab;

	tab = ft_split(line, ' ');
	return (tab);
}

int	verif_wight_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] > 32)
			return (1);
		i++;
	}
	return (0);
}

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

char	*vide_quote(char **tab)
{
	int		i;
	int		j;
	char	*str;
	char	*new_str;

	str = NULL;
	str = remake_str_bis(tab);
	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * (strlen(str) + 1));
	if (!new_str)
		return (free(str), NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		while (str[i] == '"' || str[i] == 39)
			++i;
		if (str[i] == '\0')
			break ;
		new_str[j] = str[i];
		++j;
	}
	new_str[j] = '\0';
	return (free(str), new_str);
}
