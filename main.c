/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:46:58 by nabboud           #+#    #+#             */
/*   Updated: 2024/07/07 15:09:07 by nabboud          ###   ########.fr       */
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

void	fail_execve(int execve_status, char **args, char **envp, t_general *g)
{
	if (execve_status != 0)
	{
		perror("execve");
		free_tab(args);
		free_tab(envp);
		free(g->line);
		if (g->handle_ikou)
		{
			free(g->handle_ikou);
			g->handle_ikou = NULL;
		}
		if (g->tab_file)
			free_tab(g->tab_file);
		if (g->tab_dir)
			free_tab(g->tab_dir);
		if (g->tab_cmd)
			free_tab(g->tab_cmd);
		if (g->tab_pipe)
			free_tab(g->tab_pipe);
		if (g->handle_eko)
			free(g->handle_eko);
		g->exval = 126;
	}
	ft_fprintf(2, "commande not found\n");
}

void	ft_execve(char *line, char *tab_cmd, t_general *g)
{
	char	**args;
	char	**envp;
	char	*path_cmd;
	int		execve_status;

	(void)line;
	envp = get_local_env(&g->local_env);
	delete_env(&g->local_env);
	g_flag = 1;
	args = cmd_args(tab_cmd);
	path_cmd = based_path(args[0], g);
	if (path_cmd == NULL)
	{
		g->exval = 127;
		ft_fprintf(2, "No such file or directory command not found\n");
		return (free_tab(args));
	}
	if (g->check_pipe == 1)
	{
		free_tab(g->tab_pipe);
	}
	execve_status = execve(path_cmd, args, envp);
	fail_execve(execve_status, args, envp, g);
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
}

int	main(int ac, char **av, char **envp)
{
	t_general	g;

	(void)ac;
	(void)av;
	init(&g);
	main_signal();
	init_local_env(&g.local_env, envp);
	while (1)
	{
		g.prompt = ft_get_prompt();
		g.line = readline(g.prompt);
		free(g.prompt);
		g.line = trim_space(g.line);
		if (g.line == NULL)
			break ;
		if (*g.line == '\0')
			continue ;
		init_tab(&g);
	}
	delete_env(&g.local_env);
	rl_clear_history();
	if (WIFEXITED(g.status))
		return (WEXITSTATUS(g.status));
	else
		return (0);
}
