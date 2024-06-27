/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_project.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/27 11:54:59 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include "env/env.h"

int	cd_based_path(char *cmd, t_general *g)
{
	int		i;
	int		status;
	char	**tab;
	char	*str;
	char	*tmp;
	char	*path_env;

	status = access(cmd, X_OK);
	if (status == 0)
		return (1);
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
			return (1);
		free(tmp);
		++i;
	}
	if (*cmd != '$')
	{
		g->$ = 1;
		ft_fprintf(2, " No such file or directory");
	}
	return (0);
}

void	cd_project(char **tab, t_general *g)
{
	char	*user;
	char	*tmp;
	char	path[PATH_MAX];


	if (tab[1] == NULL)
	{
		tmp = ft_strjoin("OLDPWD=",  getcwd(path, PATH_MAX));
		ft_add_var(&g->local_env, tmp, true);
		free(tmp);
		user = getenv("USER");
		tmp = ft_strjoin("/home/", user);
		chdir(tmp);
		free(tmp);
		tmp = ft_strjoin("PWD=",  getcwd(path, PATH_MAX));
		ft_add_var(&g->local_env, tmp, true);
		free(tmp);
		return ;
	}
	else if (tab[2] != NULL)
	{
		g->$ = 1;
		ft_fprintf(2, " too many arguments\n");
		return ;
	}
	if (cd_based_path(tab[1], g) == 1)
	{
		getcwd(path, PATH_MAX);
		tmp = ft_strjoin("OLDPWD=",  getcwd(path, PATH_MAX));
		ft_add_var(&g->local_env, tmp, true);
		free(tmp);
		chdir(tab[1]);
	}
	tmp = ft_strjoin("PWD=",  getcwd(path, PATH_MAX));
	ft_add_var(&g->local_env, tmp, true);
	free(tmp);
}
