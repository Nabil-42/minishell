/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:46:58 by nabboud           #+#    #+#             */
/*   Updated: 2024/06/22 09:10:09 by nabil            ###   ########.fr       */
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
			return (printf("minishell: %s: 6 command not found\n", cmd),
				exit(128 + status), NULL);
		if (cmd[i] == '/')
			return (printf("minishell: %s: No such file or directory\n", cmd),
				exit(128 + status), NULL);
		++i;
	}
	return (printf("minishell: %s: 7 command not found\n", cmd), exit(128
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
	tmp = ft_strjoin("minishell:", handl);
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
	int		execve_status;

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
int	is_delimiter(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	count_tokens(char *str)
{
	int	count;
	int	i;
	int	inside_token;

	count = 0;
	i = 0;
	inside_token = 0;
	int in_single_quotes = 0;
	int in_double_quotes = 0;
	while (str[i] != '\0')
	{
		// Gérer les guillemets simples
		if (str[i] == '\'')
		{
			if (in_single_quotes)
			{
				in_single_quotes = 0;
			}
			else if (!in_double_quotes)
			{
				in_single_quotes = 1;
			}
			// Gérer les guillemets doubles
		}
		else if (str[i] == '"')
		{
			if (in_double_quotes)
			{
				in_double_quotes = 0;
			}
			else if (!in_single_quotes)
			{
				in_double_quotes = 1;
			}
		}
		// Compter les tokens seulement si on n'est pas dans des guillemets
		if (!in_single_quotes && !in_double_quotes)
		{
			if (is_delimiter(str[i]))
			{
				// Vérifier pour les délimiteurs doubles
				if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<'
						&& str[i + 1] == '<'))
				{
					count++;
					i++; // Sauter le deuxième caractère du délimiteur double
				}
				else
				{
					count++;
				}
				inside_token = 0;
			}
			else
			{
				if (!inside_token)
				{
					count++;
					inside_token = 1;
				}
			}
		}
		i++;
	}
	return (count);
}

void	multiple_pipe(char *line, t_general *g)
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
}
void	init(t_general *g)
{
	g->tab_cmd = NULL;
	g->tab_dir = NULL;
	g->line = NULL;
	g->prompt = NULL;
	g->command_before_pipe = NULL;
	g->command_after_pipe = NULL;
	g->status = 0;
	g->count = 0;
	g->nbr_token = 0;
	g->$ = 0;
	g->index_dir = 0;
}
int boucle(t_general *g, t_env *local_env)
{
	int i;
	int k;
	k = 0;
	i = 0;
	while (i < g->nbr_token
			|| (g->nbr_token == 0 && i == 0))
		{
			// printf("%s\n", g->tab_cmd[1]);
			// printf("%s\n", g->tab_dir[i]);
			// printf("%s\n", g->tab_dir[0]);
			// printf("%s\n", g->tab_cmd[1]);
			if (builtin(g->tab_cmd[k], local_env, g)
				&& i == (g->nbr_token - 1))
			{
				break;
			}
			i++;
			k += 2;
		}
		i = 0;
		k = 0;
		g->index_dir = 0;
		if (g->tab_dir[0] != NULL)
			free_tab(g->tab_dir);
		if (g->tab_cmd[0] != NULL)
			free_tab(g->tab_cmd);
		return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_general	g;
	t_env		local_env;

	
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
		if (*g.line == '\0')
			continue ;
		add_history(g.line);
		g.nbr_token = count_tokens(g.line);
		g.tab_cmd = split_str(g.line, &g.nbr_token);
		g.tab_dir = split_delimiters(g.line, &g.nbr_token);
		boucle(&g, &local_env);
		continue;
		// multiple_pipe(g.line, &g);
		// pipe_while(&g);
		free_tab(g.tab_cmd);
		free_tab(g.tab_dir);
		free(g.line);
		flag = 0;
	}
	rl_clear_history();
	if (WIFEXITED(g.status))
		return (WEXITSTATUS(g.status));
	else
		return (0);
}
