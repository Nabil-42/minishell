/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:17:26 by tissad            #+#    #+#             */
/*   Updated: 2024/08/08 14:54:15 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../parsing/parsenv.h"
#include "env.h"

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

void	ft_set_var(t_env *env, char *key, char *value)
{
	t_var	*var;

	var = create_var(key, EQUAL, value);
	if (!var)
		ft_printf("minishell : can not create %s\n", key);
	add_var(env, var);
}
