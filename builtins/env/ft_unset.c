/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:17:26 by tissad            #+#    #+#             */
/*   Updated: 2024/08/08 14:53:54 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

static int	cond(void *key, void *content);

void	ft_unset(t_general *g, char **args)
{
	t_list	**lst;
	t_env	*env;
	int		hash;
	int		i;

	g->flag_eko_n = 3;
	env = &g->local_env;
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

static int	cond(void *key, void *content)
{
	t_var	*var;

	var = (t_var *)content;
	return (var->env_flag && ft_strncmp(key, var->key, ft_strlen(key)));
}
