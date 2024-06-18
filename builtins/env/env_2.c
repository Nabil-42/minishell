/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:33:54 by nabil             #+#    #+#             */
/*   Updated: 2024/06/18 20:49:53 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "env/env.h"

unsigned int hash_function(const char *key, unsigned int table_size)
{
    uint32_t hash;
    const uint32_t fnv_prime = 16777619U;
    
	hash = 2166136261U;
	while (*key)
	{
        hash ^= (uint8_t)*key++;
        hash *= fnv_prime;
    }
    return (hash % table_size);
}

char	*get_key(char *env_var)
{
	size_t	len;

	len = 0;
	while (env_var[len] && env_var[len] != '=')
	{
		len++;
	}
	return (ft_substr(env_var, 0, len));
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
		new_var = ft_lstnew((void *)ft_strdup(envp[i]));
		ft_lstadd_back(&local_env->env_p[hash], new_var);
		free(key);
		local_env->nb_var++;
		i++;
	}
}