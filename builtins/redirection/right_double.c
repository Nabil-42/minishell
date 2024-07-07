/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:16:58 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 21:50:52 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

void	skip_white_space(char *str, int i, char *output)
{
	int	j;

	j = 0;
	++i;
	while (str[i] && str[i] <= 32)
	{
		++i;
	}
	while (str[i] && j < 1023)
	{
		output[j++] = str[i++];
	}
	output[j] = '\0';
}

char	*skip(char *str)
{
	char	*buff;
	int		i;
	int		k;

	k = 0;
	i = 0;
	buff = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (buff == NULL)
		return (NULL);
	while (str[i] && (str[i] <= 32 || str[i] == '.' || str[i] == '/'))
	{
		i++;
	}
	while (str[i] && str[i] != 32)
	{
		buff[k] = str[i];
		++i;
		++k;
	}
	buff[k] = '\0';
	return (buff);
}

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

int	handle_single_redirection(char *filename, char *redir_type, t_general *g)
{
	int	fd;

	if (strcmp(redir_type, ">") == 0)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (strcmp(redir_type, ">>") == 0)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (strcmp(redir_type, "<") == 0)
	{
		fd = open(filename, O_RDONLY);
	}
	else
	{
		fprintf(stderr, "Unknown redirection type: %s\n", redir_type);
		return (g->exval = 602, -1);
	}
	if (fd < 0)
	{
		ft_fprintf(2, "%s: 2 No such file or directory\n", filename);
		return (g->exval = 1, -1);
	}
	return (fd);
}

int	apply_redirection(int fd, char *redir_type, t_general *g)
{
	if (strcmp(redir_type, ">") == 0 || strcmp(redir_type, ">>") == 0)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			return (perror("dup2"), close(fd), g->exval = 998, -1);
		}
	}
	else if (strcmp(redir_type, "<") == 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			return (perror("dup2"), close(fd), g->exval = 997, -1);
		}
	}
	else
	{
		fprintf(stderr, "Unknown redirection type: %s\n", redir_type);
		g->exval = 999;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
