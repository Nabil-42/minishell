/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:16:27 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 21:40:08 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include "env/env.h"

int	is_number(const char *str)
{
	while (isspace(*str))
		str++;
	if (*str == '"')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '"')
		str++;
	if (!isdigit(*str))
		return (0);
	while (*str)
	{
		if (*str == '"')
		{
			str++;
			continue ;
		}
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(char **tab, t_general *g)
{
	int	exit_code;

	if (tab[1] == NULL)
		exit(g->exval);
	if (tab[2] != NULL)
	{
		ft_fprintf(2, "exit: too many arguments\n");
		exit(1);
	}
	if (!is_number(tab[1]))
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n", tab[1]);
		exit(2);
	}
	exit_code = ft_atoi_bis(tab[1]);
	exit(exit_code % 256);
}
