/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:16:58 by nabil             #+#    #+#             */
/*   Updated: 2024/08/11 22:07:55 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

extern volatile sig_atomic_t	g_flag;

void	restore_standard_fds(int saved_stdout, int saved_stdin, t_general *g)
{
	if (dup2(saved_stdout, STDOUT_FILENO) < 0 || dup2(saved_stdin,
			STDIN_FILENO) < 0)
	{
		g->exval = 1;
		perror("dup2");
	}
	close(saved_stdout);
	close(saved_stdin);
}

char	*expand_hd(char *line, t_general *g)
{
	t_echo	*beko;

	beko = malloc(sizeof(t_echo));
	if (!beko)
		return (NULL);
	init_eko(beko, g);
	echo_herdoc(line, beko, g);
	free(beko);
	return (ft_strdup(g->handle_eko));
}

void	herdoc(t_general *g, char *eof)
{
	char	*line;
	int		fd;

	fd = open("heredoc_temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		g->exval = 1;
		return ;
	}
	main_signal_tris();
	while (1)
	{
		line = readline("> ");
		if (strcmp(line, eof) == 0 || line == NULL)
		{
			free(line);
			break ;
		}
		line = expand_hd(line, g);
		ft_fprintf(fd, "%s\n", line);
		free(line);
	}
	close(fd);
}

int	herd(t_general *g, char *filename)
{
	int	fd;

	pipe_while_bis(g, &filename);
	fd = open("heredoc_temp.txt", O_RDONLY);
	if (fd < 0)
		return ((g->exval = 2), perror("open"), -1);
	return (fd);
}
