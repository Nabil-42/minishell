/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:25:04 by nabil             #+#    #+#             */
/*   Updated: 2024/07/13 20:21:10 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

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

int	handle_variable_expansion_n(char *str, t_echo *eko, int *i)
{
	char	*variable_env;
	char	*name;
	int		k;

	variable_env = extract_env_variable_name_n(str, i);
	if (variable_env == NULL)
		return (0);
	name = getenv(variable_env);
	free(variable_env);
	if (name == NULL)
		return (0);
	k = 0;
	while (name[k])
	{
		eko->line[eko->j++] = name[k++];
	}
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
			if (!handle_variable_expansion_n(str, eko, &i))
				++i;
			continue ;
		}
		copy_normal_char_n(str, eko, &i);
	}
	eko->line[eko->j] = '\0';
	return (0);
}
