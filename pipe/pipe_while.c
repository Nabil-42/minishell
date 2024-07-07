/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:12:17 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 16:11:24 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

extern volatile sig_atomic_t	g_flag;

void	init_pipe(t_general *g, int *comm_pipe)
{
	if (pipe(comm_pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	g->i_pipe = 0;
	g->k_pipe = 0;
	g->received_value = 0;
	g->prev_pipe_read = -1;
}

void	child(t_general *g, int *pipefd, int *comm_pipe)
{
	int	return_value;

	if (g->prev_pipe_read != -1)
		(dup2(g->prev_pipe_read, 0), close(g->prev_pipe_read));
	if (g->i_pipe < g->count)
		(close(pipefd[0]), dup2(pipefd[1], 1), close(pipefd[1]));
	(close(comm_pipe[0]), ft_execve(g->tab_cmd[0], g->tab_cmd[0], g));
	return_value = g->exval;
	write(comm_pipe[1], &return_value, sizeof(return_value));
	exit(EXIT_FAILURE);
}

void	parent(t_general *g, int *pipefd, pid_t pid, int *comm_pipe)
{
	if (g->prev_pipe_read != -1)
		close(g->prev_pipe_read);
	if (g->i_pipe < g->count)
		(close(pipefd[1]), g->prev_pipe_read = pipefd[0]);
	waitpid(pid, &g->status, 0);
	if (g->i_pipe == g->count)
		(close(comm_pipe[1]), read(comm_pipe[0], &g->received_value, 3),
			g->exval = g->received_value, close(comm_pipe[0]));
}

void	pipe_while(t_general *g)
{
	int		pipefd[2];
	int		comm_pipe[2];
	pid_t	pid;

	g_flag = 1;
	init_pipe(g, comm_pipe);
	while (g->i_pipe <= g->count)
	{
		if (g->i_pipe < g->count && pipe(pipefd) == -1)
			(perror("pipe"), exit(EXIT_FAILURE));
		pid = fork();
		if (pid == -1)
			(perror("fork"), exit(EXIT_FAILURE));
		else if (pid == 0)
			child(g, pipefd, comm_pipe);
		else
		{
			parent(g, pipefd, pid, comm_pipe);
			(g->i_pipe++);
			(g->k_pipe++);
		}
	}
	if (g->prev_pipe_read != -1)
		close(g->prev_pipe_read);
}
