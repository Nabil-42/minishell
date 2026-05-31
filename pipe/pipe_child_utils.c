/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_while_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:12:17 by nabil             #+#    #+#             */
/*   Updated: 2024/08/09 21:49:06 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

extern volatile sig_atomic_t	g_flag;

void	child_bis(t_general *g, char **tab)
{
	herdoc(g, tab[0]);
	exit(EXIT_FAILURE);
}

void	pipe_while_bis(t_general *g, char **tab)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		(perror("fork"), exit(EXIT_FAILURE));
	else if (pid == 0)
		child_bis(g, tab);
	else
		parent(g, pid);
}
