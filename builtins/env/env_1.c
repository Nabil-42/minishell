/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:17:26 by tissad            #+#    #+#             */
/*   Updated: 2024/07/07 22:16:20 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_export(t_general *g, char **args, t_echo *eko)
{
	int	i;

	g->flag_eko_n = 3;
	echo(args, eko, g);
	args = ft_split(eko->line, ' ');
	i = 0;
	while (args[i])
	{
		ft_add_var(&g->local_env, args[i], true);
		g->local_env.nb_var++;
		i++;
	}
}

void	ft_unset(t_env *env, char **args, t_general *g)
{
	t_list	**lst;
	int		hash;
	int		i;

	g->flag_eko_n = 3;
	i = 1;
	while (args[i])
	{
		hash = hash_function(args[i], MAX_ENV);
		lst = &env->env_p[hash];
		ft_lstdelcond(lst, args[i], cond, del);
		env->nb_var--;
		i++;
	}
}

void	delete_envp(char **envp)
{
	while (*envp)
	{
		free(*envp);
		envp++;
	}
}

void	ft_env(t_env *env, t_general *g)
{
	char	**local_env;
	int		i;

	g->flag_eko_n = 3;
	local_env = get_local_env(env);
	i = 0;
	while (local_env[i])
	{
		if (local_env[i])
			printf("%s\n", local_env[i]);
		i++;
	}
	delete_envp(local_env);
	free(local_env);
}

char	*ft_getenv(t_env *env, char *key)
{
	t_list	*lst_iter;
	t_var	*var;
	int		hash;

	hash = hash_function(key, MAX_ENV);
	lst_iter = env->env_p[hash];
	while (lst_iter)
	{
		var = (t_var *)(lst_iter->content);
		if (var->env_flag && ft_strcmp(key, var->key) == 0)
		{
			return (var->value);
		}
		lst_iter = lst_iter->next;
	}
	return (NULL);
}
