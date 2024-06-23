/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:07:16 by nabil             #+#    #+#             */
/*   Updated: 2024/06/23 17:16:13 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

int	echo_verif_1(t_echo *eko, char *str, int *i, t_general *g)
{
	eko->flag_i = 0;
	eko->flag = 0;
	if ((str[*i] == '"'))
	{
		while (str[*i])
		{
			++*i;
			if (str[*i] == '"')
			{
				echo_take_of_double_quote(str, eko, *i, g);
				++*i;
				eko->flag_i = 1;
				eko->dir = *i;
				eko->flag = 1;
			}
			if (eko->flag == 1)
				break ;
		}
		if (eko->flag == 1)
			return (2);
		return (printf("minishell: %s: command not found\n", str), 1);
	}
	return (0);
}
int	echo_verif_2(t_echo *eko, char *str, int *i)
{
	eko->flag = 0;
	if (str[*i] == 39)
	{
		while (str[*i])
		{
			++*i;
			if (str[*i] == 39)
			{
				echo_take_of_simple_quote(str, eko, *i);
				++*i;
				eko->flag = 1;
				eko->dir = *i;
			}
			if (eko->flag == 1)
				break ;
		}
		if (eko->flag == 1)
			return (2);
		return (printf("minishell: %s: command not found\n", str), 1);
	}
	return (0);
}
void	echo_verif_4(t_echo *eko, int *i, char *str)
{
	if (eko->dir != *i)
	{
		while (str[eko->dir] && (str[eko->dir] != '<' && str[eko->dir] != '>'))
		{
			eko->line[eko->j] = str[eko->dir];
			eko->j++;
			eko->dir++;
		}
		eko->line[eko->j] = '\0';
	}
}

void	echo_verif_3(t_echo *eko, t_general *g)
{
	if (g->tab_dir[0] == NULL)
		return ;	
	g->check_dir = 1;
	handle_redirections_and_execute(eko->line, g, g->nbr_token, g->tab_dir);
	// if (g->tab_dir[g->index_dir] != NULL && g->tab_dir[g->index_dir][0] == '>')
	// 	{
	// 		if (g->tab_dir[g->index_dir][1] != '\0')
	// 		{
	// 			if (g->tab_dir[g->index_dir][1] == '>')
	// 				(direction_double(g->tab_cmd[g->index_dir + 1], eko, g, eko->line));
	// 		}
	// 		else if (g->tab_dir[g->index_dir] != NULL && g->tab_dir[g->index_dir][0] == '>')
	// 			(direction(g->tab_cmd[g->index_dir + 1], eko, g, eko->line));
	// 	}
	// 	g->check_dir = 1;
	// 	g->index_dir++;
	// 	printf("%d\n", g->index_dir);
	// }
}

char	*echo_verif_quote(char *str, t_echo *eko, t_general *g)
{
	int	i;

	eko->line[0] = '\0';
	i = 0;
	while (str[i])
	{
		if (echo_verif_1(eko, str, &i, g) == 2)
			continue ;
		else if (echo_verif_1(eko, str, &i, g) == 1)
			return (NULL);
		if (echo_verif_2(eko, str, &i) == 2)
			continue ;
		else if (echo_verif_2(eko, str, &i) == 1)
			return (NULL);
		if (eko->flag_i == 0)
			++i;
	}
	if (eko->line[0] == '\0')
		return (eko->line);
	echo_verif_4(eko, &i, str);
	echo_verif_3(eko, g);
	if (g->check_dir == 1)
		return (NULL);
	return (eko->line);
}

void	echo_args(char *str, t_echo *eko, char *tmp, t_general *g)
{
	if (tmp[0] == '\0')
	{
		dollar_n(str, eko, g);
		free_tab(eko->tab);
		return ;
	}
	echo_verif_3(eko, g);
	if (g->check_dir == 1)
		return ;
	printf("%s", tmp);
	free_tab(eko->tab);
}
