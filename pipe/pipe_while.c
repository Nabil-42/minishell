/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:12:17 by nabil             #+#    #+#             */
/*   Updated: 2024/08/09 13:03:23 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

extern volatile sig_atomic_t	g_flag;

void	child(t_general *g)
{
	main_signal_bis();
	ft_execve(g->tab_cmd[0], g->tab_cmd[0], g);
	exit(EXIT_FAILURE);
}

void	parent(t_general *g, pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g->exval = WEXITSTATUS(status);
	if (g_flag == 2)
		g->exval = 130;
	if (g_flag == 3)
		g->exval = 131;
}

void	pipe_while(t_general *g)
{
	pid_t	pid;

	g_flag = 1;
	main_signal_bis();
	pid = fork();
	if (pid == -1)
		(perror("fork"), exit(EXIT_FAILURE));
	else if (pid == 0)
		child(g);
	else
		parent(g, pid);
}
