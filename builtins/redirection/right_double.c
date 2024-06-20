/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:16:58 by nabil             #+#    #+#             */
/*   Updated: 2024/06/20 17:59:14 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

int	direction_double(char *str, t_echo *eko, t_general *g, char *line)
{
	char	output[1024];
	int		j;
	int		fd;
	int		saved_stdout;
	int		i;

	j = 0;
	i = 0;
	(void)g;
	(void)eko;
	while (str[i] && str[i] <= 32)
		++i;
	while (str[i] && j < 1023)
		output[j++] = str[i++];
	output[j] = '\0';
	fd = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		(perror("open"), exit(EXIT_FAILURE));
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
		(perror("dup"), close(fd), exit(EXIT_FAILURE));
	if (dup2(fd, STDOUT_FILENO) < 0)
		(perror("dup2"), close(fd), exit(EXIT_FAILURE));
	(close(fd), printf("%s\n", line));
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
		(perror("dup2"), close(saved_stdout), exit(EXIT_FAILURE));
	return (close(saved_stdout), 0);
}

int direction_double_$(char *str, t_echo *eko, t_general *g, int $)
{
	char	output[1024];
	int		j;
	int		fd;
	int		saved_stdout;
	int		i;

	j = 0;
	i = 0;
	(void)eko;
	(void)g;
	while (str[i] && str[i] <= 32)
		++i;
	while (str[i] && j < 1023)
		output[j++] = str[i++];
	output[j] = '\0';
	fd = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		(perror("open"), exit(EXIT_FAILURE));
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
		(perror("dup"), close(fd), exit(EXIT_FAILURE));
	if (dup2(fd, STDOUT_FILENO) < 0)
		(perror("dup2"), close(fd), exit(EXIT_FAILURE));
	(close(fd), printf("%d\n", $));
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
		(perror("dup2"), close(saved_stdout), exit(EXIT_FAILURE));
	return (close(saved_stdout), 0);
}

int	direction_double_n(char *str, t_echo *eko, t_general *g, char *line)
{
	char output[1024];
	int j = 0;
	int fd;
	int saved_stdout;
	int i;

	i = 0;
	(void)g;
	(void)eko;
	while (str[i] && str[i] <= 32)
		++i;
	while (str[i] && j < 1023)
		output[j++] = str[i++];
	output[j] = '\0';
	fd = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		(perror("open"), exit(EXIT_FAILURE));
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
		(perror("dup"), close(fd), exit(EXIT_FAILURE));
	if (dup2(fd, STDOUT_FILENO) < 0)
		(perror("dup2"), close(fd), exit(EXIT_FAILURE));
	(close(fd), printf("%s", line));
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
		(perror("dup2"), close(saved_stdout), exit(EXIT_FAILURE));
	return (close(saved_stdout), 0);
}