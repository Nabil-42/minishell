/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:16:27 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 11:21:06 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include "env/env.h"

int	is_number(const char *str)
{
	// Ignore leading white spaces
	while (isspace(*str))
		str++;
	// Ignore leading double quotes
	if (*str == '"')
		str++;
	// Check for leading plus or minus sign
	if (*str == '+' || *str == '-')
		str++;
	// Ignore leading double quotes again if any after the sign
	if (*str == '"')
		str++;
	// Check if the next character is a digit
	if (!isdigit(*str))
		return (0);
	// Loop through the rest of the string
	while (*str)
	{
		// Ignore double quotes in between
		if (*str == '"')
		{
			str++;
			continue ;
		}
		// If any non-digit character is found, return 0
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
