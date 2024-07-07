/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:54:43 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 21:44:10 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include "env/env.h"

void	init_eko(t_echo *eko, t_general *g)
{
	eko->len_str = 200;
	eko->i = 0;
	eko->j = 0;
	eko->exval = g->exval;
	eko->line = NULL;
	eko->flag_i = 0;
	eko->flag = 0;
}

void	missingknow(t_echo *eko, t_general *g)
{
	(void)eko;
	g->flag_eko_n = 2;
}

int	execute_command(char **tab, t_echo *eko, t_env *local_env, t_general *g)
{
	(void)local_env;
	if (ft_strcmp(tab[0], "echo") == 0 && ft_strcmp(tab[1], "exval?") == 0)
		return (missingknow(eko, g), free_tab(eko->tab), free_tab(g->petit_tab),
			1);
	if (ft_strcmp(tab[0], "echo") == 0)
		return (echo(g->petit_tab, eko, g), free_tab(eko->tab),
			free_tab(g->petit_tab), 1);
	if (ft_strcmp(tab[0], "cd") == 0)
		return (cd_project(tab, g), free_tab(eko->tab), free_tab(g->petit_tab),
			1);
	if (ft_strcmp(tab[0], "pwd") == 0)
		return (pwd(tab, g), free_tab(eko->tab), free_tab(g->petit_tab), 1);
	if (ft_strcmp(tab[0], "env") == 0)
		return (ft_env(local_env, g), free_tab(eko->tab),
			free_tab(g->petit_tab), 1);
	if (ft_strcmp(tab[0], "export") == 0)
		return (ft_export(g, tab, eko), free_tab(eko->tab),
			free_tab(g->petit_tab), 1);
	if (ft_strcmp(tab[0], "unset") == 0)
		return (ft_unset(local_env, tab, g), free_tab(eko->tab),
			free_tab(g->petit_tab), 1);
	if (ft_strcmp(tab[0], "exit") == 0)
		return (ft_exit(tab, g), free_tab(eko->tab), free_tab(g->petit_tab), 1);
	(free_tab(eko->tab), free_tab(g->petit_tab));
	return (0);
}

int	builtin(char *line, t_env *local_env, t_general *g)
{
	t_echo	eko;
	int		result;
	char	*test;

	eko.tab = NULL;
	test = remake_str_bis(g->tab_cmd);
	g->petit_tab = ft_split(test, ' ');
	free(test);
	eko.tab = ft_split(line, ' ');
	init_eko(&eko, g);
	if (!eko.tab[0])
		return (free_tab(eko.tab), 0);
	if (ft_strcmp(eko.tab[0], "echo") != 0 && ft_strcmp(eko.tab[0], "cd") != 0
		&& ft_strcmp(eko.tab[0], "pwd") != 0 && ft_strcmp(eko.tab[0],
			"env") != 0 && ft_strcmp(eko.tab[0], "exit") != 0
		&& eko.tab[1] == NULL)
		return (free_tab(eko.tab), free_tab(g->petit_tab), 0);
	if (ft_strcmp(eko.tab[0], "echo") == 0 && eko.tab[1] == NULL)
	{
		g->flag_eko_n = 6;
		free_tab(eko.tab);
		return (free_tab(g->petit_tab), 1);
	}
	result = execute_command(eko.tab, &eko, local_env, g);
	return (result);
}
