/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 23:04:41 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 12:20:29 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

int	count_segments(const char *cmd)
{
	int	count;

	count = 1;
	while (*cmd != '\0')
	{
		if (*cmd == '|')
		{
			count++;
		}
		cmd++;
	}
	return (count);
}

char	**allocate_result(int count)
{
	char	**result;

	result = malloc((count + 1) * sizeof(char *));
	if (result == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (result);
}

char	*clean_token(char *token)
{
	char	*end;

	while (*token == ' ')
		token++;
	end = token + strlen(token) - 1;
	while (end > token && *end == ' ')
		end--;
	end[1] = '\0';
	return (ft_strdup(token));
}

char	**split_by_pipe(char *cmd)
{
	int		segment_count;
	char	**result;
	char	*cmd_copy;
	int		i;
	char	*token;

	segment_count = count_segments(cmd);
	result = allocate_result(segment_count);
	cmd_copy = ft_strdup(cmd);
	if (cmd_copy == NULL)
		(perror("strdup"), exit(EXIT_FAILURE));
	i = 0;
	token = strtok(cmd_copy, "|");
	while (token != NULL)
	{
		result[i] = clean_token(token);
		if (result[i] == NULL)
			(perror("strdup"), exit(EXIT_FAILURE));
		i++;
		token = strtok(NULL, "|");
	}
	result[i] = NULL;
	free(cmd_copy);
	return (result);
}
