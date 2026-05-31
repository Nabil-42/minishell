/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:56:37 by tissad            #+#    #+#             */
/*   Updated: 2024/08/09 21:17:04 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

void	delete_var(t_var *var)
{
	free(var->key);
	free(var->value);
	free(var);
}

void	del(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	delete_var(var);
	content = NULL;
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
	env->nb_var = 0;
}

void	delete_envp(char **envp)
{
	while (*envp)
	{
		free(*envp);
		envp++;
	}
}
