/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_poubelle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/08/08 13:22:05 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

void	boucle_remake(char **tab, char *new_str)
{
	int	j;
	int	k;
	int	i;

	i = 0;
	k = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j])
		{
			new_str[k] = tab[i][j];
			++k;
			++j;
		}
		if (tab[i + 1] != NULL)
			new_str[k] = ' ';
		++k;
		++i;
	}
	k--;
	new_str[k] = '\0';
}

char	*remake_str_bis(char **tab)
{
	char	*new_str;

	if (tab[0] == NULL)
		return (NULL);
	new_str = malloc(sizeof(char) * PATH_MAX + 1);
	if (new_str == NULL)
		return (NULL);
	boucle_remake(tab, new_str);
	return (new_str);
}

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
