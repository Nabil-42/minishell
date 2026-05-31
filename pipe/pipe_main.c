/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:12:17 by nabil             #+#    #+#             */
/*   Updated: 2024/08/09 22:32:12 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include <errno.h>
#include <libft.h>
#include <readline/history.h>
#include <readline/readline.h>

extern volatile sig_atomic_t	g_flag;

pid_t	init_pipeline(char **tab_pipe, int i, int *pipe_fds)
{
	pid_t	pid;

	if (tab_pipe[i + 1] != NULL)
		if (pipe(pipe_fds) == -1)
			(perror("pipe"), exit(EXIT_FAILURE));
	pid = fork();
	if (pid == -1)
		(perror("fork"), exit(EXIT_FAILURE));
	return (pid);
}

void	enfant_pipeline(int i, int input_fd, char **tab_pipe, int *pipe_fds)
{
	if (i > 0)
	{
		if (dup2(input_fd, 0) == -1)
			(perror("dup2 input_fd"), exit(EXIT_FAILURE));
	}
	if (tab_pipe[i + 1] != NULL)
	{
		if (dup2(pipe_fds[1], 1) == -1)
			(perror("dup2 pipe_fds[1]"), exit(EXIT_FAILURE));
	}
	if (input_fd != 0)
		close(input_fd);
	close(pipe_fds[1]);
	close(pipe_fds[0]);
}

void	parent_pipeline(int *input_fd, char **tab_pipe, int i, int *pipe_fds)
{
	if (*input_fd != 0)
		close(*input_fd);
	if (tab_pipe[i + 1] != NULL)
	{
		close(pipe_fds[1]);
		*input_fd = pipe_fds[0];
	}
	else
	{
		(close(pipe_fds[0]));
		(close(pipe_fds[1]));
	}
}

static int	child_exec(char **tab_pipe, t_general *g, int i)
{
	int	status;

	status = handle_redirections_and_execute(tab_pipe[i], g);
	delete_env(&g->local_env);
	return (status);
}

void	execute_pipeline(char **tab_pipe, t_general *g)
{
	int		pipe_fds[2];
	int		input_fd;
	pid_t	pid;
	int		i;
	int		valeur;

	valeur = 0;
	input_fd = 0;
	i = 0;
	g_flag = 1;
	while (tab_pipe[i] != NULL)
	{
		pid = init_pipeline(tab_pipe, i, pipe_fds);
		if (pid == 0)
		{
			enfant_pipeline(i, input_fd, tab_pipe, pipe_fds);
			exit(child_exec(tab_pipe, g, i));
		}
		else
			parent_pipeline(&input_fd, tab_pipe, i, pipe_fds);
		i++;
	}
	while (wait(&valeur) > 0)
		if (WIFEXITED(valeur))
			g->exval = WEXITSTATUS(valeur);
}
