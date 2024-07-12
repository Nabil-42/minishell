/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:07:16 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 22:23:21 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

int	echo_verif_1_bis(t_echo *eko, char *str, int *i, t_general *g)
{
	eko->flag_i = 0;
	eko->flag = 0;
	if ((str[*i] == '"'))
	{
		while (str[*i])
		{
			++*i;
			if (str[*i] == '"')
			{
				echo_take_of_double_quote(str, eko, *i, g);
				++*i;
				eko->flag_i = 1;
				eko->dir = *i;
				eko->flag = 1;
			}
			if (eko->flag == 1)
				break ;
		}
		if (eko->flag == 1)
			return (2);
		return (ft_fprintf(2, "minishell: %s: 1 Command not found ", str), 1);
	}
	return (0);
}

int	echo_verif_1(t_echo *eko, char *str, int *i, t_general *g)
{
	eko->flag_i = 0;
	eko->flag = 0;
	if ((str[*i] == '"'))
	{
		while (str[*i])
		{
			++*i;
			if (str[*i] == '"')
			{
				echo_take_of_double_quote(str, eko, *i, g);
				++*i;
				eko->flag_i = 1;
				eko->dir = *i;
				eko->flag = 1;
			}
			if (eko->flag == 1)
				break ;
		}
		if (eko->flag == 1)
			return (2);
		return (ft_fprintf(2, "minishell: %s: 1 Command not found ", str), 1);
	}
	return (0);
}

int	echo_verif_2(t_echo *eko, char *str, int *i, t_general *g)
{
	eko->flag = 0;
	if (str[*i] == 39)
	{
		while (str[*i])
		{
			++*i;
			if (str[*i] == 39)
			{
				echo_take_of_simple_quote(str, eko, *i, g);
				++*i;
				eko->flag = 1;
				eko->dir = *i;
			}
			if (eko->flag == 1)
				break ;
		}
		if (eko->flag == 1)
			return (2);
		return (ft_fprintf(2, "minishell: %s: 2 Command not found ", str), 1);
	}
	return (0);
}

void	echo_verif_4(t_echo *eko, int *i, char *str)
{
	if (eko->dir != *i)
	{
		while (str[eko->dir] && (str[eko->dir] != '<' && str[eko->dir] != '>'))
		{
			eko->line[eko->j] = str[eko->dir];
			eko->j++;
			eko->dir++;
		}
		eko->line[eko->j] = '\0';
	}
}

char	*echo_verif_quote(char *str, t_echo *eko, t_general *g)
{
	int	i;
	int	k;

	eko->line[0] = '\0';
	i = 0;
	while (str[i])
	{
		k = echo_verif_1(eko, str, &i, g);
		if (k == 2)
			continue ;
		else if (k == 1)
			return (NULL);
		k = echo_verif_2(eko, str, &i, g);
		if (k == 2)
			continue ;
		else if (k == 1)
			return (NULL);
		if (eko->flag_i == 0)
			++i;
	}
	if (eko->line[0] == '\0')
		return (eko->line);
	echo_verif_4(eko, &i, str);
	return (eko->line);
}

void	echo_args(char *str, t_echo *eko, char *tmp, t_general *g)
{
	if (tmp[0] == '\0')
	{
		dollar_n(str, eko, g);
		free_tab(eko->tab);
		return ;
	}
	free_tab(eko->tab);
}
