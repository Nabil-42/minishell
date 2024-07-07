/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:17:26 by tissad            #+#    #+#             */
/*   Updated: 2024/07/07 22:13:56 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	del(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	delete_var(var);
	free(content);
	content = NULL;
}

int	cond(void *key, void *content)
{
	t_var	*var;

	var = (t_var *)content;
	return (var->env_flag && ft_strncmp(key, var->key, ft_strlen(key)));
}

void	delete_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < MAX_ENV)
	{
		ft_lstclear(&env->env_p[i], del);
		i++;
	}
}

t_list	*exist_env_var(char *key, t_list *lst)
{
	t_list	*lst_iter;
	t_var	*var;

	lst_iter = lst;
	while (lst_iter)
	{
		var = (t_var *)lst_iter->content;
		if (ft_strncmp(key, var->key, ft_strlen(key)) == 0)
			return (lst_iter);
		lst_iter = lst_iter->next;
	}
	return (lst_iter);
}

void	ft_add_var(t_env *env, char *env_str, bool flag)
{
	t_list	*new;
	t_list	*elt;
	char	*value;
	char	*key;
	int		hash;

	key = get_key(env_str);
	value = get_value(env_str);
	hash = hash_function(key, MAX_ENV);
	elt = exist_env_var(key, env->env_p[hash]);
	if (!elt)
	{
		new = ft_lstnew((void *)create_var(key, value, flag));
		ft_lstadd_back(&env->env_p[hash], new);
	}
	else
	{
		rest_value((t_var *)elt->content, value);
		free(key);
	}
}
