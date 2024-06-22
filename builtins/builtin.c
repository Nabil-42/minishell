/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:54:43 by nabil             #+#    #+#             */
/*   Updated: 2024/06/22 08:51:31 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include "env/env.h"

void	init_eko(t_echo *eko, char *line, t_general *g)
{
	(void)line;
	eko->len_str = 200;
	eko->i = 0;
	eko->j = 0;
	eko->$ = g->$;
	eko->line = NULL;
	eko->flag_i = 0;
	eko->flag = 0;
	eko->tab = NULL;
	eko->check_dir = 0;
	
}

void	missingknow(t_echo *eko, t_general *g)
{
	echo_verif_3_$(eko, g);
	if (eko->check_dir == 1)
		return ;
	printf("%d\n", eko->$);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	if (*line == '\0')
		return (1);
	while (line[i])
	{
		if (is_delimiter(line[i]))
			return (1);
		++i;
	}
	return (0);
}

int	execute_command(char **tab, t_echo *eko, t_env *local_env, t_general *g)
{
	if (ft_strcmp(tab[0], "echo") == 0 && ft_strcmp(tab[1], "$?") == 0)
		return (missingknow(eko, g), free_tab(eko->tab), 1);
	if (ft_strcmp(tab[0], "echo") == 0)
		return (echo(tab, eko, g), free_tab(eko->tab), 1);
	if (ft_strcmp(tab[0], "cd") == 0)
		return (cd_project(tab, local_env, g), free_tab(eko->tab), 1);
	if (ft_strcmp(tab[0], "pwd") == 0)
		return (pwd(tab), free_tab(eko->tab), 1);
	if (ft_strcmp(tab[0], "env") == 0)
		return (ft_env(local_env), free_tab(eko->tab), 1);
	if (ft_strcmp(tab[0], "exit") == 0)
		return (ft_exit(tab, g), free_tab(eko->tab), 1);
	return (0);
}

int	builtin(char *line, t_env *local_env, t_general *g)
{
	t_echo	eko;
	int		result;

	init_eko(&eko, line, g);
	eko.tab = ft_split(line, ' ');
	if (ft_strcmp(eko.tab[0], "echo") != 0 
		&& ft_strcmp(eko.tab[0], "cd") != 0
		&& ft_strcmp(eko.tab[0], "pwd") != 0
		&& ft_strcmp(eko.tab[0],"env") != 0
		&& ft_strcmp(eko.tab[0], "exit") != 0
		&& eko.tab[1] == NULL)
		return (free(eko.tab), 0);
	if (ft_strcmp(eko.tab[0], "echo") == 0
		&& eko.tab[1] == NULL)
	{
		return (free_tab(eko.tab), 1);
	}
	result = execute_command(eko.tab, &eko, local_env, g);
	return (result);
}
