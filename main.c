/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:46:58 by nabboud           #+#    #+#             */
/*   Updated: 2024/08/12 00:51:39 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/includes/libft.h"
#include "minishell.h"
#include <errno.h>
#include <libft.h>
#include <readline/history.h>
#include <readline/readline.h>

#define PATH_MAX 4096

extern volatile sig_atomic_t	g_flag;

int	ft_execve_bis(char *path_cmd, char **args, t_general *g)
{
	char	**envp;
	int		execve_status;

	g->i_based_p = -1;
	envp = get_local_env(&g->local_env);
	if (path_cmd == NULL)
	{
		(delete_env(&g->local_env), full_free(g), free_tab(args));
		return (free_tab(envp), exit(g->exval), 0);
	}
	if (g->check_pipe == 1)
		free_tab(g->tab_pipe);
	if (args[1] == NULL && g->nbr_dir > 0 && g->tab_file[0] == NULL)
	{
		(delete_env(&g->local_env), ft_fprintf(2, "syntax error\n"));
		(full_free(g), free_tab(args), free_tab(envp), free(path_cmd));
		return ((g->exval = 2), 2);
	}
	execve_status = execve(path_cmd, args, envp);
	if (execve_status != 0)
	{
		(((free(path_cmd)), (free_tab(args)), (("minishell :execve"))));
		free_tab(envp);
	}
	return (execve_status);
}

int	ft_execve(char *line, char *tab_cmd, t_general *g)
{
	int		i;
	char	*path_cmd;
	char	*tmp;
	char	**expand_args;

	(void) line;
	expand_args = ft_split_quote(tab_cmd);
	i = 0;
	while (expand_args[i])
	{
		tmp = expand_hd(expand_args[i], g);
		expand_args[i] = tmp;
		i++;
	}
	g->i_based_p = 0;
	path_cmd = based_path(expand_args[0], g);
	return (ft_execve_bis(path_cmd, expand_args, g));
}

void	init(t_general *g)
{
	g->tab_cmd = NULL;
	g->tab_dir = NULL;
	g->tab_pipe = NULL;
	g->line = NULL;
	g->prompt = NULL;
	g->command_before_pipe = NULL;
	g->command_after_pipe = NULL;
	g->status = 0;
	g->count = 0;
	g->nbr_dir = 0;
	g->nbr_pipe = 0;
	g->exval = 0;
	g->index_dir = 0;
	g->check_dir = 0;
	g->check_pipe = 0;
	g->nbr_file = 0;
	g->tab_file = NULL;
	g->handle_eko = NULL;
	g->flag_eko_n = 0;
	g->path = NULL;
	g->petit_tab = NULL;
	g->flag_error = 0;
	g->handle_ikou = NULL;
	g->status = 0;
	g_flag = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_general	g;

	(void)ac;
	(void)av;
	init(&g);
	init_local_env(&g.local_env, envp);
	while (1)
	{
		main_signal();
		g.prompt = ft_get_prompt();
		g.line = readline(g.prompt);
		free(g.prompt);
		g.line = trim_space(g.line);
		if (g.line == NULL)
			break ;
		if (*g.line == '\0')
		{
			free(g.line);
			continue ;
		}
		init_tab(&g);
	}
	delete_env(&g.local_env);
	rl_clear_history();
	return (0);
}
