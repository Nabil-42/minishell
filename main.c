/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:46:58 by nabboud           #+#    #+#             */
/*   Updated: 2024/07/01 19:38:51 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/includes/libft.h"
#include "minishell.h"
#include <errno.h>
#include <libft.h>
#include <readline/history.h>
#include <readline/readline.h>

#define PATH_MAX 4096

extern volatile sig_atomic_t	flag;


void	ft_execve(char *line, char *tab_cmd, t_general *g)
{
	char	**args;
	char	**envp;
	char	*path_cmd;
	int		execve_status;

	(void)line;
	envp = get_local_env(&g->local_env);
	delete_env(&g->local_env);	
	flag = 1;
	args = cmd_args(tab_cmd);
	path_cmd = based_path(args[0], g);
	if (path_cmd == NULL)
	    return(free_tab(args));
	if (g->check_pipe == 1)
	{
		free_tab(g->tab_pipe);
	}
	execve_status = execve(path_cmd, args, envp);
	if (execve_status != 0)
	{
		free_tab(args);
		free(path_cmd);
		return (printf("minishell: %s: trouver msg derreur\n", args[0]),
			g->$ = 2, (void)1);
	}
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
	g->$ = 0;
	g->index_dir = 0;
	g->check_dir = 0;
	g->check_pipe = 0;
	g->nbr_file = 0;
	g->tab_file = NULL;
	g->handle_eko = NULL;
	g->flag_eko_n = 0;
	g->path = NULL;
	g->petit_tab = NULL;

}
int boucle(t_general *g)
{
	
	if (g->nbr_pipe != 0)
	{
		execute_pipeline(g->tab_pipe, g);
	}
	else {
		handle_redirections_and_execute(g->line, g);
	}
	free_tab(g->tab_pipe);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_general	g;

	(void)envp;
	(void)ac;
	(void)av;
	g.status = 0;
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
		{
		     continue;
		}
		add_history(g.line);
		g.nbr_pipe = count_pipe(g.line);
		g.tab_pipe = split_by_pipe(g.line);
		boucle(&g);
		free(g.line);
		flag = 0;
	}
	delete_env(&g.local_env);
	rl_clear_history();
	if (WIFEXITED(g.status))
		return (WEXITSTATUS(g.status));
	else
		return (0);
}
