/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:20:23 by nabboud           #+#    #+#             */
/*   Updated: 2024/06/25 20:49:15 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

void echo_verif_3_$(t_echo *eko, t_general *g)
{
	int	i;

	i = 0;
	if (g->tab_dir == NULL)
		return ;
	while (i < g->nbr_dir)
	{
		if (g->tab_dir[i][0] == '|')
			return ;
		if (g->tab_dir[i] != NULL && g->tab_dir[i][0] == '>')
		{
			if (g->tab_dir[i][1] != '\0')
			{
				if (g->tab_dir[i][1] == '>')
					direction_double_$(g->tab_cmd[i + 1], eko, g, g->$);
			}
			else if (g->tab_dir[i] != NULL && g->tab_dir[i][0] == '>')
				direction_$(g->tab_cmd[i + 1], eko, g, g->$);
		}
		g->check_dir = 1;
		++i;
	}
}

void	echo_verif_3_n(t_echo *eko, t_general *g)
{
	int	i;

	i = 0;
	if (g->tab_dir == NULL)
		return ;
	while (i < g->nbr_dir)
	{
		if (g->tab_dir[i][0] == '|')
			return ;
		if (g->tab_dir[i] != NULL && g->tab_dir[i][0] == '>')
		{
			if (g->tab_dir[i][1] != '\0')
			{
				if (g->tab_dir[i][1] == '>')
					direction_double(g->tab_cmd[i + 1], eko, g, eko->line);
			}
			else if (g->tab_dir[i] != NULL && g->tab_dir[i][0] == '>')
				direction(g->tab_cmd[i + 1], eko, g, eko->line);
		}
		g->check_dir = 1;
		++i;
	}
}
