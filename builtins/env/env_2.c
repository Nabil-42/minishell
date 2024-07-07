/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:17:26 by tissad            #+#    #+#             */
/*   Updated: 2024/07/07 22:16:50 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

unsigned int	hash_function(const char *key, unsigned int table_size)
{
	uint32_t		hash;
	const uint32_t	fnv_prime = 16777619U;

	hash = 2166136261U;
	while (*key)
	{
		hash ^= (uint8_t) * key++;
		hash *= fnv_prime;
	}
	return (hash % table_size);
}

char	*get_key(char *env_var)
{
	size_t	len;

	len = 0;
	while (env_var[len] && env_var[len] != '=')
		len++;
	return (ft_substr(env_var, 0, len));
}

char	*get_value(char *env_var)
{
	size_t	len;

	len = 0;
	while (env_var[len] && env_var[len] != '=')
		len++;
	len++;
	return (ft_substr(env_var, len, ft_strlen(env_var) - len));
}

t_var	*create_var(char *key, char *value, bool env_flag)
{
	t_var	*var;

	var = malloc(sizeof(t_var) * 1);
	if (!var)
		return (NULL);
	var->env_flag = env_flag;
	var->key = key;
	var->value = value;
	return (var);
}

void	delete_var(t_var *var)
{
	free(var->key);
	free(var->value);
}
