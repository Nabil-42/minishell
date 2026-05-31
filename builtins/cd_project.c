/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_project.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/08/11 22:14:00 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include "env/env.h"
#include <sys/stat.h>
#include <sys/types.h>

char	*cd_based_path(char *path, t_general *g)
{
	struct stat	path_stat;

	path = expand_hd(ft_strdup(path), g);
	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (path);
	}
	else
	{
		g->exval = 1;
		return (free(path), ("minishell: stat:"), NULL);
	}
	if (*path != '$')
	{
		g->status = 1;
		g->exval = 1;
		ft_fprintf(2, "minishell: No such file or directory\n");
	}
	free(path);
	return (NULL);
}

void	cd_project_2(t_general *g)
{
	g->exval = 1;
	ft_fprintf(2, " too many arguments\n");
	g->flag_eko_n = 3;
	return ;
}

void	cd_without_args(t_general *g)
{
	char	*home;

	ft_set_var(&g->local_env, ft_strdup("OLDPWD"), \
	ft_getenv(&g->local_env, "PWD"));
	home = ft_getenv(&g->local_env, "HOME");
	if (chdir(home) != 0)
	{
		perror("minishell: chdir");
		free(home);
		return ;
	}
	ft_set_var(&g->local_env, ft_strdup("PWD"), home);
	g->flag_eko_n = 3;
	return ;
}

void	cd_project(char **tab, t_general *g)
{
	char	*new_path;
	char	path_buf[PATH_MAX];

	if (tab[1] == NULL)
		return (cd_without_args(g));
	else if (tab[2] != NULL)
		return (cd_project_2(g));
	new_path = cd_based_path(tab[1], g);
	if (new_path)
	{
		ft_set_var(&g->local_env, ft_strdup("OLDPWD"), ft_getenv(&g->local_env,
				"PWD"));
		if (chdir(new_path) != 0)
			perror("minishell: chdir");
		ft_set_var(&g->local_env, ft_strdup("PWD"), \
		ft_strdup(getcwd(path_buf, PATH_MAX)));
		free(new_path);
	}
	g->flag_eko_n = 3;
}
