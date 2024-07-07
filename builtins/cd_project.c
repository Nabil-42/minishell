/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_project.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/07/07 11:20:45 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include "env/env.h"

int	check_access_in_path(char *cmd, char *path) 
{
    char *str;
    char *tmp;
    int status;

    str = ft_strjoin(path, "/");
    if (!str) return 0;

    tmp = ft_strjoin(str, cmd);
    free(str);
    if (!tmp) return 0;

    status = access(tmp, X_OK);
    free(tmp);
    return (status == 0);
}

int cd_based_path(char *cmd, t_general *g) 
{
    int status;
    char **tab;
    char *path_env;
    int i;

    status = access(cmd, X_OK);
    if (status == 0)
    	return 1;
    path_env = getenv("PATH");
    tab = ft_split(path_env, ':');
    if (!tab)
    	return 0;
    i = -1;
    while (tab[++i] != NULL) 
    {
        if (check_access_in_path(cmd, tab[i])) 
	     return (free_tab(tab), 1);
    }
    free_tab(tab);
    if (*cmd != '$') 
    {
        g->status = 1;
	g->exval = 1;
        ft_fprintf(2, "1 No such file or directory\n");
    }
    return 0;
}

void	cd_project_2(t_general *g)
{
		g->exval = 1;
		ft_fprintf(2, " too many arguments\n");
		g->flag_eko_n = 3;
		return ;
}


void	cd_project_bis(char *user, t_general *g, char *path, char *tmp)
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
		g->flag_eko_n = 3;
		return ;
}

void	cd_project(char **tab, t_general *g)
{
	char	*user;
	char	*tmp;
	char	path[PATH_MAX];

	tmp = NULL;
	user = NULL;
	if (tab[1] == NULL)
	     return (cd_project_bis(user, g, path, tmp));
	else if (tab[2] != NULL)
	{
		return (cd_project_2(g));
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
	g->flag_eko_n = 3;
}
