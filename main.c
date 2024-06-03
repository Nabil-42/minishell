/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:46:58 by nabboud           #+#    #+#             */
/*   Updated: 2024/06/03 22:32:48 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <libft.h>
#include "lib/libft/includes/libft.h"
#include <readline/history.h>
#include <readline/readline.h>

extern volatile sig_atomic_t flag;

char *verif_directoty(char *cmd, int status)
{
	int i;
	
	i = 0;
	while(cmd[i])
	{
		if (cmd[i] == '\\' || cmd[i] == ';')
			return (printf("minishell: %s: command not found\n", cmd), exit(128
			+ status), NULL);
		if (cmd[i] == '/')
			return (printf("minishell: %s: No such file or directory\n", cmd), exit(128
			+ status), NULL);
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

	tmp = ft_strjoin("-> ", getcwd(path, PATH_MAX));
	prompt = ft_strjoin(tmp, " ");
	free(tmp);
	return (prompt);
}

char	**cmd_args(char *line)
{
	char	**tab;

	tab = ft_split(line, ' ');
	return (tab);
}

void	ft_execve(char *line)
{
	char	**args;
	char	*path_cmd;
	int		execve_status;
	char	*new_line;

	flag = 1;
	new_line = verif_quote(line);
	args = cmd_args(new_line);
	verif_quote(args[0]);
	path_cmd = based_path(args[0]);
	execve_status = execve(path_cmd, args, NULL);
	if (execve_status != 0)
	{
		free_tab(args);
		free(path_cmd);
		return (printf("minishell: %s: trouver msg derreur\n", args[0]),
			exit(128 + execve_status));
	}
}
int verif_wight_space(char *line)
{
	int i;
	
	i = 0;
	while(line[i])
	{
		if (line[i] > 32)
			return (1);
		i++;
	}
	return (0);
}
void init(t_general *g)
{
	g->line = NULL;
	g->prompt = NULL;
	g->status = 0;
}

int	main(void)
{
	t_general g;

	init(&g);
	g.status = 0;
	main_signal();
	while (1)
	{
		g.prompt = ft_get_prompt();
		g.line = readline(g.prompt);
		if (g.line == NULL)
           		break;
		add_history(g.line);
		pipe_while(&g);
		free(g.prompt);
		free(g.line);
		flag = 0;
	}
	free(g.prompt);
	rl_clear_history();
	if (WIFEXITED(g.status))
		return (WEXITSTATUS(g.status));
	else
		return (0);
}

/*
int	main(void)
{
	char *line;
	char *prompt;
	//pid_t pid;
	int status;

	status = 0;
	prompt = ft_get_prompt();
	line = readline(prompt);
	while (line)
	{
		if (ft_strlen(line) <= 1)
		{
			prompt = ft_get_prompt();
			line = readline(prompt);
			continue ;
		}
		add_history(line);
		if (verif_wight_space(line) == 0)
		{
			prompt = ft_get_prompt();
			line = readline(prompt);
			continue ;
		}
		printf("%s\n", line);
		free(prompt);
		free(line);
		prompt = ft_get_prompt();
		line = readline(prompt);
	}
	free(prompt);
	rl_clear_history();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (0);
}
*/
