/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:34:49 by nabil             #+#    #+#             */
/*   Updated: 2024/06/18 20:49:56 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "env/env.h"

void	init_local_env(t_env *local_env, char **envp)
{
	int	i;

	i = 0;
	while (i < MAX_ENV)
	{
		local_env->env_p[i] = NULL;
		i++;
	}
	local_env->nb_var = 0;
	dup_env(local_env, envp);
}



char **get_local_env(t_env *env)
{
	char	**local_env;
	t_list	*lst_iter;
	int		i;
	int		j;

	local_env = malloc(sizeof(void *) * (env->nb_var + 1));
	if (!local_env)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (i < MAX_ENV)
	{
		lst_iter = env->env_p[i];
		while (lst_iter)
		{
			local_env[j] = (char *)lst_iter->content;
			lst_iter = lst_iter->next;
			j++;
		}
		i++;
	}
	local_env[j] = NULL;
	return (local_env);
}

void	del(void *content)
{
	free(content);
}

int	cond(void *value, void *content)
{
	return (ft_strncmp(value, content, ft_strlen(value)));
}