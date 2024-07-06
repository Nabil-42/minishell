/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:46:58 by nabboud           #+#    #+#             */
/*   Updated: 2024/07/07 00:53:29 by nabil            ###   ########.fr       */
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
	{
		g->$ = 127;
		ft_fprintf(2, "command not found\n");
		return(free_tab(args));
	}
	if (g->check_pipe == 1)
	{
		free_tab(g->tab_pipe);
	}
	execve_status = execve(path_cmd, args, envp);
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
		g->$ = 126;
	}
	ft_fprintf(2, "commande not found\n");
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
	g->flag_error = 0;
	g->handle_ikou = NULL;
}
int 	brut(t_general *g)
{
	if (ft_strncmp(g->line, "$PWD", 3) == 0)
	{
		g->$ = 126;
		ft_fprintf(2, "error folder\n");
		return (1);
	}
	if (ft_strncmp(g->line, "$EMPTY", 5) == 0)
	{
		g->$ = 0;
		return (1);
	}
	return 0;
}

void boucle(t_general *g)
{
	if ((g->nbr_pipe != 0 && g->tab_pipe[0] == NULL)
		|| (g->nbr_pipe >= 1 && g->tab_pipe[g->nbr_pipe] == NULL))
	{
		ft_fprintf(2, " 1 error synthax\n");
		g->$ = 2;
		free_tab(g->tab_pipe);
		return;
	}
	if (g->tab_pipe[g->nbr_pipe + 1] != NULL
		&& g->nbr_pipe != 0)
	{
		ft_fprintf(2, "2 error synthax\n");
		g->$ = 127;
		free_tab(g->tab_pipe);
		free_tab(g->tab_cmd);
		return;
	}
	if ((g->nbr_dir != 0 && g->tab_cmd[0] == NULL))
	{
		ft_fprintf(2, "3 error synthax\n");
		g->$ = 2;
		free_tab(g->tab_pipe);
		free_tab(g->tab_cmd);
		return;
	}
	if (g->tab_cmd)
	{
		free_tab(g->tab_cmd);
		g->tab_cmd = NULL;
	}
	if (brut(g))
	{
		free_tab(g->tab_pipe);
		return;
	}
	if (g->nbr_pipe != 0)
	{
		execute_pipeline(g->tab_pipe, g);
	}
	else {
		handle_redirections_and_execute(g->line, g);
	}
	free_tab(g->tab_pipe);
	if (g->tab_file)
		free_tab(g->tab_file);
	if (g->tab_dir)
		free_tab(g->tab_dir);
	if (g->tab_cmd)
		free_tab(g->tab_cmd);
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
		g.tab_cmd = split_str(g.line, &g.nbr_dir);
		g.nbr_dir = count_redirections(g.line);
		// printf("0 %s\n", g.tab_cmd[0]);
		// printf("1 %s\n", g.tab_cmd[1]);
		// printf("pipe 1 %s\n", g.tab_pipe[2]);
		// printf("nbr dir %d\n", g.nbr_dir);
		// printf("nbr pipe %d\n", g.nbr_pipe);
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
