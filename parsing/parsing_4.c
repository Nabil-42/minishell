/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:02:53 by nabil             #+#    #+#             */
/*   Updated: 2024/07/04 21:08:08 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"

char	**cmd_args(char *line)
{
	char	**tab;

	tab = ft_split(line, ' ');
	return (tab);
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

char	*verif_directoty(char *cmd, int status, t_general *g)
{
	int	i;
	(void)status;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\' || cmd[i] == ';')
			return (printf("minishell: %s: 6 command not found\n", cmd),
			g->$ = 52, NULL);
		if (cmd[i] == '/')
		{
			g->$ = 1;
			return (printf("minishell: %s: No such file or directory\n", cmd),
				g->$ = 62, NULL);
			
		}
		++i;
	}
	return (printf("minishell: %s: command not found\n", cmd), 
		g->$ = 22, NULL);
}

char	*based_path(char *cmd, t_general *g)
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
	return (free_tab(tab), verif_directoty(cmd, status, g), NULL);
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
