/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_project.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/19 13:13:13 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "../includes/minishell.h"
#include "env/env.h"

int cd_based_path(char *cmd, t_general *g)
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
			return (free_tab(tab), 1);
		free(tmp);
		++i;
	}
	if (*cmd != '$')
	{
		g->$ = 1;
		ft_fprintf(2, " Aucun fichier ou dossier de ce type");	
	}
	return (0);
}

void cd_project(char **tab, t_env *local_env, t_general *g)
{
        char *user;
        char *tmp;
	char path[PATH_MAX];
        
	if (tab[2] != NULL)
	{
		g->$ = 1;
		ft_fprintf(2, " trop d'arguments");
		return;
	}
        if (tab[1] == NULL)
        {
                user = getenv("USER"); 
                tmp = ft_strjoin("/home/", user);
                chdir(tmp);
                free(tmp);
                free_tab(tab);
		tmp = ft_strjoin("PWD=",  getcwd(path, PATH_MAX));
		ft_export(local_env, tmp);
                return;
        }
        if (cd_based_path(tab[1], g) == 1)
        {       
                chdir(tab[1]);
                free_tab(tab);        
        }
		tmp = ft_strjoin("PWD=",  getcwd(path, PATH_MAX));
		ft_export(local_env, tmp);
		free(tmp);
}
