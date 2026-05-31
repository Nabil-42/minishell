/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:54:59 by tissad            #+#    #+#             */
/*   Updated: 2024/08/08 14:52:41 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/parsenv.h"
#include "env.h"
#include "minishell.h"
#include <libft.h>

t_var	*create_var(char *key, int op, char *value)
{
	t_var	*var;

	var = malloc(sizeof(t_var) * 1);
	if (!var)
	{
		ft_printf("minishell : export : malloc error\n");
		return (NULL);
	}
	var->key = key;
	var->op = op;
	if (var->op == NOTHING)
		var->env_flag = false;
	else
		var->env_flag = true;
	var->value = value;
	return (var);
}

static void	dup_env(t_env *local_env, char **envp)
{
	t_list	*new_var;
	t_var	*var;
	int		hash;
	int		i;

	i = 0;
	while (envp[i])
	{
		var = (t_var *)pars_var(envp[i], "minishell : init env");
		if (!var->key)
		{
			delete_var(var);
			i++;
			continue ;
		}
		var->env_flag = true;
		hash = hash_function(var->key, MAX_ENV);
		new_var = ft_lstnew((void *)var);
		ft_lstadd_back(&local_env->env_p[hash], new_var);
		local_env->nb_var++;
		i++;
	}
}

static void	init_pwd(t_env *local_env)
{
	char	path[PATH_MAX];

	ft_set_var(local_env, ft_strdup("PWD"), ft_strdup(getcwd(path, PATH_MAX)));
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
	init_pwd(local_env);
}
