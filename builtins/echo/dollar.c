/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:06:47 by nabil             #+#    #+#             */
/*   Updated: 2024/06/20 17:58:46 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

char	*extract_env_variable_name(char *str, int *i)
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
		k++;
	}
	variable_env[k] = '\0';
	return (variable_env);
}

int	handle_variable_expansion(char *str, t_echo *eko, int *i)
{
	char	*variable_env;
	char	*name;
	int		k;

	variable_env = extract_env_variable_name(str, i);
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
void	copy_normal_char(char *str, t_echo *eko, int *i)
{
	char	*itoua;
	int		k;

	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		k = 0;
		itoua = ft_itoa(eko->$);
		while (itoua[k])
		{
			eko->line[eko->j] = itoua[k];
			++eko->j;
			k++;
		}
		++*i;
	}
	else
		(eko->line[eko->j++] = str[*i]);
	++(*i);
}
int	dollar(char *str, t_echo *eko, t_general *g)
{
	int	i;

	i = 0;
	eko->j = 0;
	while (str[i])
	{
		if (eko->check_dir == 1)
			return (0);
		if (str[i] == '$' && str[i + 1] != '\0' && str[eko->i + 1] != '?')
		{
			if (!handle_variable_expansion(str, eko, &i))
				return (0);
			continue ;
		}
		copy_normal_char(str, eko, &i);
	}
	echo_verif_3(eko, g);
	if (eko->check_dir == 1)
		return (0);
	eko->line[eko->j] = '\0';
	printf("%s\n", eko->line);
	return (0);
}
