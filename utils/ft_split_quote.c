/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 23:04:41 by nabil             #+#    #+#             */
/*   Updated: 2024/08/12 11:27:57 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

#include <stdlib.h>
#include <string.h>

static char	*skip_spc(char *str)
{
	while ((*str) == ' ')
	{
		str++;
	}
	return (str);
}

static char	*extract_token_1(char **start)
{
	char	token[500];
	char	*str;
	int		i;
	int		j;
	char	quote;

	str = *start;
	i = 0;
	j = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i++];
			token[j++] = quote;
			while (str[i] && str[i] != quote)
				token[j++] = str[i++];
			if (str[i] == quote)
				token[j++] = str[i++]; 
		}
		else if (str[i] != ' ')
			token[j++] = str[i++];
	}
	token[j] = '\0';
	*start = &str[i];
	return (strdup(token));
}

static char	**init_args(int nb)
{
	char	**args;

	args = malloc(sizeof(char *) * nb);
	if (!args)
		exit(EXIT_FAILURE);
	return (args);
}

char	**ft_split_quote(char *str)
{
	int		index;
	char	*start;
	char	**args;

	index = 0;
	start = str;
	args = init_args(500);
	while (*start != '\0')
	{
		start = skip_spc(start);
		if (*start == '\0')
			break ;
		args[index] = extract_token_1(&start);
		index++;
	}
	args[index] = NULL;
	return (args);
}

