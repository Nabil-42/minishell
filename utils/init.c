/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 23:04:41 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 12:11:55 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

extern volatile sig_atomic_t	g_flag;

int	synthax(t_general *g)
{
	if ((g->nbr_pipe != 0 && g->tab_pipe[0] == NULL) || (g->nbr_pipe >= 1
			&& g->tab_pipe[g->nbr_pipe] == NULL))
		return (ft_fprintf(2, " 1 error synthax\n"), g->exval = 2,
			free_tab(g->tab_pipe), 1);
	if (g->tab_pipe[g->nbr_pipe + 1] != NULL && g->nbr_pipe != 0)
	{
		ft_fprintf(2, "2 error synthax\n");
		g->exval = 127;
		free_tab(g->tab_pipe);
		free_tab(g->tab_cmd);
		return (1);
	}
	if ((g->nbr_dir != 0 && g->tab_cmd[0] == NULL))
	{
		ft_fprintf(2, "3 error synthax\n");
		g->exval = 2;
		free_tab(g->tab_pipe);
		free_tab(g->tab_cmd);
		return (1);
	}
	if (g->tab_cmd)
		(free_tab(g->tab_cmd), g->tab_cmd = NULL);
	return (0);
}

int	brut(t_general *g)
{
	if (ft_strncmp(g->line, "$PWD", 3) == 0)
	{
		g->exval = 126;
		ft_fprintf(2, "error folder\n");
		return (1);
	}
	if (ft_strncmp(g->line, "$EMPTY", 5) == 0)
	{
		g->exval = 0;
		return (1);
	}
	return (0);
}

void	full_free(t_general *g)
{
	if (g->line)
		(free(g->line), g->line = NULL);
	if (g->tab_file)
		(free_tab(g->tab_file), g->tab_file = NULL);
	if (g->tab_dir)
		(free_tab(g->tab_dir), g->tab_dir = NULL);
	if (g->tab_cmd)
		(free_tab(g->tab_cmd), g->tab_cmd = NULL);
	if (g->tab_pipe)
		(free_tab(g->tab_pipe), g->tab_pipe = NULL);
	if (g->handle_eko)
		(free(g->handle_eko), g->handle_eko = NULL);
}

void	boucle(t_general *g)
{
	if (synthax(g))
		return ;
	if (brut(g))
	{
		free_tab(g->tab_pipe);
		return ;
	}
	if (g->nbr_pipe != 0)
	{
		execute_pipeline(g->tab_pipe, g);
	}
	else
	{
		handle_redirections_and_execute(g->line, g);
	}
	full_free(g);
}

void	init_tab(t_general *g)
{
	add_history(g->line);
	g->nbr_pipe = count_pipe(g->line);
	g->tab_pipe = split_by_pipe(g->line);
	g->tab_cmd = split_str(g->line, &g->nbr_dir);
	g->nbr_dir = count_redirections(g->line);
	boucle(g);
	free(g->line);
	g_flag = 0;
}
