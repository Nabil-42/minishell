/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:25:04 by nabil             #+#    #+#             */
/*   Updated: 2024/08/12 12:07:18 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

char	*extract_env_variable_name_n(char *str, int *i)
{
	char	*variable_env;
	int		k;

	variable_env = malloc(PATH_MAX + 1);
	k = 0;
	if (variable_env == NULL)
		return (NULL);
	++(*i);
	while (((str[*i] >= 'A' && str[*i] <= 'Z') || (str[*i] >= 'a'
				&& str[*i] <= 'z')) && str[*i] != '\0')
	{
		variable_env[k] = str[*i];
		++*i;
		++k;
	}
	variable_env[k] = '\0';
	return (variable_env);
}

int	handle_variable_expansion_n(char *str, t_echo *eko, int *i, t_general *g)
{
	char	*variable_env;
	char	*name;
	int		k;

	variable_env = extract_env_variable_name_n(str, i);
	if (variable_env == NULL)
		return (0);
	name = ft_getenv(&g->local_env, variable_env);
	free(variable_env);
	if (name == NULL)
		return (0);
	k = 0;
	while (name[k])
	{
		eko->line[eko->j++] = name[k++];
	}
	free(name);
	return (1);
}

void	copy_normal_char_n(char *str, t_echo *eko, int *i)
{
	eko->line[eko->j++] = str[*i];
	++(*i);
}

int	dollar_n(char *str, t_echo *eko, t_general *g)
{
	int	i;

	(void)g;
	i = 0;
	eko->j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!handle_variable_expansion_n(str, eko, &i, g))
				++i;
			continue ;
		}
		copy_normal_char_n(str, eko, &i);
	}
	eko->line[eko->j] = '\0';
	return (0);
}
