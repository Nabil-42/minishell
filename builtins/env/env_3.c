/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:17:26 by tissad            #+#    #+#             */
/*   Updated: 2024/07/07 22:13:51 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rest_value(t_var *var, char *new_value)
{
	free(var->value);
	var->value = new_value;
}

void	dup_env(t_env *local_env, char **envp)
{
	t_list	*new_var;
	char	*key;
	int		hash;
	int		i;

	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i]);
		hash = hash_function(key, MAX_ENV);
		new_var = ft_lstnew((void *)create_var(key, get_value(envp[i]), true));
		ft_lstadd_back(&local_env->env_p[hash], new_var);
		local_env->nb_var++;
		i++;
	}
}

void	init_local_env(t_env *local_env, char **envp)
{
	int	i;

	(void)envp;
	i = 0;
	while (i < MAX_ENV)
	{
		local_env->env_p[i] = NULL;
		i++;
	}
	local_env->nb_var = 0;
	dup_env(local_env, envp);
}

char	*tvar_to_str(t_var *var)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(var->key, "=");
	str = ft_strjoin(tmp, var->value);
	free(tmp);
	return (str);
}

char	**get_local_env(t_env *env)
{
	t_list	*lst_iter;
	t_var	*var;
	char	**local_env;
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
			var = (t_var *)(lst_iter->content);
			if (var->env_flag)
				local_env[j++] = tvar_to_str(var);
			lst_iter = lst_iter->next;
		}
		i++;
	}
	local_env[j] = NULL;
	return (local_env);
}
