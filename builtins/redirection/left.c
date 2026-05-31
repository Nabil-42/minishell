/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:25:28 by nabil             #+#    #+#             */
/*   Updated: 2024/08/08 17:02:01 by nabboud          ###   ########.fr       */
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

int	handle_input_redirection(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
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
	else if (strcmp(redir_type, "<<") == 0)
	{
		return (herd(g, filename));
	}
	else
		return ((g->exval = 1),
			fprintf(stderr, "Unknown redirection type: %s\n", redir_type), -1);
	if (fd < 0)
		return (perror("open"), (g->exval = 2), -1);
	return (fd);
}

int	apply_redirection(int fd, char *redir_type, t_general *g)
{
	if (strcmp(redir_type, ">") == 0 || strcmp(redir_type, ">>") == 0)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			return (perror("dup2"), close(fd), g->exval = 1, -1);
		}
	}
	else if (strcmp(redir_type, "<") == 0 || strcmp(redir_type, "<<") == 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			return (perror("dup2"), close(fd), g->exval = 1, -1);
		}
	}
	else
	{
		fprintf(stderr, "Unknown redirection type: %s\n", redir_type);
		g->exval = 1;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
