/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:02:53 by nabil             #+#    #+#             */
/*   Updated: 2024/08/12 00:24:43 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"
#include <sys/stat.h>
#include <sys/types.h>

char	*verif_directoty(char *cmd, int status, t_general *g)
{
	int	i;

	(void)status;
	(void)g;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			perror("access");
			return (NULL);
		}
		++i;
	}
	ft_fprintf(2, "minishell: %s: command not found\n", cmd);
	return (NULL);
}

int	based_path_bis(char *cmd, t_general *g)
{
	struct stat	path_stat;
	int			status;

	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		if (stat(cmd, &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
			{
				return ((g->exval = 126),
					ft_fprintf(2, "minishell: %s: Is a directory\n", cmd), 1);
			}
		}
		else
			return ((g->exval = 127), perror("stat"), 1);
		status = access(cmd, X_OK);
		if (status != 0)
			return ((g->exval = 126),
				ft_fprintf(2, "minishell: %s: Permission denied\n", cmd), 1);
	}
	if (stat(cmd, &path_stat) == 0)
		if (S_ISDIR(path_stat.st_mode))
			return ((g->exval = 127),
				ft_fprintf(2, "minishell: %s: command not found\n", cmd), 1);
	return (0);
}

int	based_path_tris(char *cmd, t_general *g)
{
	if (based_path_bis(cmd, g))
		return (1);
	return (0);
}

char	*based_path(char *cmd, t_general *g)
{
	int		status;
	char	**tab;
	char	*str;
	char	*tmp;
	char	*path_env;

	if (based_path_tris(cmd, g))
		return (NULL);
	status = access(cmd, X_OK);
	if (status == 0)
		return (cmd);
	path_env = ft_getenv(&g->local_env, "PATH");
	((tab = ft_split(path_env, ':')), (free(path_env)));
	while (tab[++g->i_based_p])
	{
		str = ft_strjoin(tab[g->i_based_p], "/");
		tmp = ft_strjoin(str, cmd);
		free(str);
		status = access(tmp, X_OK);
		if (status == 0)
			return (free_tab(tab), tmp);
		free(tmp);
	}
	return ((g->exval = 127), verif_directoty(cmd, status, g), free_tab(tab),
		NULL);
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
