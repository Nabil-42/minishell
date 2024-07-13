/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:16:27 by nabil             #+#    #+#             */
/*   Updated: 2024/07/13 16:32:48 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include "env/env.h"

int	is_number(const char *str)
{
	while (isspace(*str))
		str++;
	if (*str == '"')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '"')
		str++;
	if (!isdigit(*str))
		return (0);
	while (*str)
	{
		if (*str == '"')
		{
			str++;
			continue ;
		}
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(char **tab, t_general *g, t_echo *eko)
{
	int	exit_code;

	if (tab[1] == NULL)
	{
		(free_tab(eko->tab),free_tab(g->petit_tab));
		delete_env(&g->local_env), full_free(g), exit(g->exval);
	}
	if (tab[2] != NULL)
	{
		(free_tab(eko->tab),free_tab(g->petit_tab));
		delete_env(&g->local_env), full_free(g);
		ft_fprintf(2, "exit: too many arguments\n"), exit(1);
	}
	if (!is_number(tab[1]))
	{
		(free_tab(eko->tab),free_tab(g->petit_tab));
		delete_env(&g->local_env), full_free(g);
		ft_fprintf(2, "exit: numeric argument required\n");
		exit(2);
	}
	exit_code = ft_atoi_bis(tab[1]);
	(free_tab(eko->tab),free_tab(g->petit_tab));
	delete_env(&g->local_env), full_free(g);
	exit(exit_code % 256);
}
