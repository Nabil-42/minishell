/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:54:43 by nabil             #+#    #+#             */
/*   Updated: 2024/08/08 13:59:24 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include "../parsing/parsenv.h"
#include "env/env.h"

extern volatile sig_atomic_t	g_flag;

void	init_eko(t_echo *eko, t_general *g)
{
	eko->len_str = 200;
	eko->i = 0;
	eko->j = 0;
	eko->exval = g->exval;
	eko->line = NULL;
	eko->flag_i = 0;
	eko->flag = 0;
	eko->k = 0;
}

void	missingknow(t_echo *eko, t_general *g)
{
	(void)eko;
	if (g_flag == 2)
		g->exval = 130;
	if (g_flag == 3)
		g->exval = 131;
	g->flag_eko_n = 2;
}
