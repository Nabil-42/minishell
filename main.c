/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:46:58 by nabboud           #+#    #+#             */
/*   Updated: 2024/06/15 16:32:38 by nabil            ###   ########.fr       */
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

char	*verif_directoty(char *cmd, int status)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\' || cmd[i] == ';')
			return (printf("minishell: %s: command not found\n", cmd), exit(128
					+ status), NULL);
		if (cmd[i] == '/')
			return (printf("minishell: %s: No such file or directory\n", cmd),
				exit(128 + status), NULL);
		++i;
	}
	return (printf("minishell: %s: command not found\n", cmd), exit(128
			+ status), NULL);
}

char	*based_path(char *cmd)
{
	int		i;
	int		status;
	char	**tab;
	char	*str;
	char	*tmp;
	char	*path_env;

	status = access(cmd, X_OK);
	if (status == 0)
		return (cmd);
	path_env = getenv("PATH");
	tab = ft_split(path_env, ':');
	i = 0;
	while (tab[i])
	{
		str = ft_strjoin(tab[i], "/");
		tmp = ft_strjoin(str, cmd);
		free(str);
		status = access(tmp, X_OK);
		if (status == 0)
			return (free_tab(tab), tmp);
		free(tmp);
		++i;
	}
	return (verif_directoty(cmd, status));
}

char	*ft_get_prompt(void)
{
	char	path[PATH_MAX];
	char	*prompt;
	char	*tmp;
	char	*handl;

	handl = getcwd(path, PATH_MAX);
	if (handl == NULL)
		return (NULL);
	tmp = ft_strjoin("-> ", handl);
	if (!tmp)
		return (NULL);
	prompt = ft_strjoin(tmp, " ");
	free(tmp);
	if (!prompt)
		return (NULL);
	return (prompt);
}

char	**cmd_args(char *line)
{
	char	**tab;

	tab = ft_split(line, ' ');
	return (tab);
}

void	ft_execve(char *line, char *tab_cmd)
{
	char	**args;
	char	*path_cmd;
	int	execve_status;
	(void)line;
	
	flag = 1;
	args = cmd_args(tab_cmd);
	path_cmd = based_path(args[0]);
	execve_status = execve(path_cmd, args, NULL);
	if (execve_status != 0)
	{
		free_tab(args);
		free(path_cmd);
		return (printf("minishell: %s: trouver msg derreur\n", args[0]),
			exit(128 + execve_status), (void)1);
	}
}
int	verif_wight_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] > 32)
			return (1);
		i++;
	}
	return (0);
}
void	init(t_general *g)
{
	g->tab_cmd = NULL;
	g->line = NULL;
	g->prompt = NULL;
	g->status = 0;
	g->command_before_pipe = NULL;
        g->command_after_pipe = NULL;
	g->count = 0;
	g->nbr_token = 0;
}
void multiple_pipe(char *line, t_general *g)
{
	char	*new_line;

	flag = 1;
	new_line = verif_quote(line);
	if (new_line == NULL || *new_line == '\0')
		return (free(new_line));
	check_redirections(new_line);
	check_special_characters(new_line);
	count_commands(new_line, g);
	free(g->line);
	g->line = new_line;
	// printf("g line = %s\n", g->line);
}

int	main(int ac, char **av, char **envp)
{
	t_general	g;
	t_env 		local_env;
	
	(void)ac;
	(void)av;
	init(&g);
	g.status = 0;
	main_signal();
	init_local_env(&local_env, envp);
	while (1)
	{
		g.prompt = ft_get_prompt();
		g.line = readline(g.prompt);
		free(g.prompt);
		if (g.line == NULL)
			break ;
		add_history(g.line);
		if (builtin(g.line, &local_env))
			continue ;
		multiple_pipe(g.line, &g);
		g.nbr_token =  count_tokens(g.line);
		g.tab_cmd = split_str(g.line, &g.nbr_token);
		// printf("gline = %s et tabcmd = %s\n",g.line, g.tab_cmd[0] );
		// printf("gline = %s et tabcmd = %s\n",g.line, g.tab_cmd[1] );
		pipe_while(&g);
		free(g.line);
		flag = 0;
	}
	rl_clear_history();
	if (WIFEXITED(g.status))
		return (WEXITSTATUS(g.status));
	else
		return (0);
}
