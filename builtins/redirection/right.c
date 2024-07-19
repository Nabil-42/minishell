/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:14:54 by nabil             #+#    #+#             */
/*   Updated: 2024/07/19 18:41:43 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

void	exe_cmd(char *cmd, t_general *g)
{
	if (builtin(cmd, &g->local_env, g))
	{	
		if (g->flag_eko_n >= 10)
			return;
		else if (g->flag_eko_n == 0 && g->handle_eko[0] != ' ')
			printf("%s\n", g->handle_eko);
		else if (g->flag_eko_n == 1)
			printf("%s", g->handle_eko);
		else if (g->flag_eko_n == 2)
			return (printf("%d\n", g->exval), (void)0);
		else if (g->flag_eko_n == 3)
			return ;
		else if (g->flag_eko_n == 4)
			(printf("%s\n", g->path), free(g->path));
		else if (g->flag_eko_n == 6)
			return (printf("\n"), (void)0);
		if (g->handle_eko != NULL)
		{
			free(g->handle_eko);
			g->handle_eko = NULL;
		}
	}
	else if (g->nbr_pipe > 0)
		return (ft_execve(cmd, cmd, g));
	else
		(pipe_while(g));
}

int	h_r_a_e(int saved_stdin, int saved_stdout, t_general *g, char *cmd)
{
	if (handle_error_1(saved_stdin, saved_stdout, g) == -1)
		return (1);
	g->nbr_dir = 0;
	g->tab_cmd = split_str(cmd, &g->nbr_dir, g);
	if (handle_error_2(g, cmd) == -1)
		return (1);
	g->tab_dir = split_delimiters(cmd, &g->nbr_dir);
	g->tab_file = split_file(cmd, &g->nbr_file);
	return (0);
}

int	h_r_a_e_bis(int fd, int saved_stdout, int saved_stdin, t_general *g)
{
	if (fd < 0)
	{
		restore_standard_fds(saved_stdout, saved_stdin, g);
		g->exval = 1;
		++g->i_right;
		return (1);
	}
	if (apply_redirection(fd, g->tab_dir[g->i_right], g) < 0)
	{
		restore_standard_fds(saved_stdout, saved_stdin, g);
		g->exval = 2;
	}
	++g->i_right;
	return (0);
}

int	handle_redirections_and_execute(char *cmd, t_general *g)
{
	int		fd;
	int		saved_stdout;
	int		saved_stdin;
	t_echo	ikou;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	g->i_right = 0;
	if (h_r_a_e(saved_stdin, saved_stdout, g, cmd))
		return (1);
	while (g->i_right < g->nbr_file)
	{
		handle_error_3(g, &fd, &g->i_right);
		if (h_r_a_e_bis(fd, saved_stdout, saved_stdin, g))
			return (1);
	}
	ikou.line = vide_quote(g->tab_cmd);
	if (ikou.line)
		g->handle_ikou = ikou.line;
	exe_cmd(ikou.line, g);
	restore_standard_fds(saved_stdout, saved_stdin, g);
	return (2);
}
