/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:02:53 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 20:54:20 by nabboud          ###   ########.fr       */
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
