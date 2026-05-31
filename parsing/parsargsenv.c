/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargsenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:06:15 by tissad            #+#    #+#             */
/*   Updated: 2024/08/12 11:15:35 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

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

	str = *start;
	i = 0;
	j = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] && (str[i] == '\"' || str[i] == '\''))
		{
			i++;
			while (str[i] && (str[i] == '\"' || str[i] == '\''))
				token[j++] = str[i++];
		}
		if (str[i] && (str[i] == '\"' || str[i] == '\'') && str[i] != ' ')
			token[j++] = str[i];
		i++;
	}
	token[j] = '\0';
	*start = &str[i];
	return (ft_strdup(token));
}

static char	**init_args(int nb)
{
	char	**args;

	args = malloc(sizeof (char *) * nb);
	if (!args)
		exit (EXIT_FAILURE);
	return (args);
}

char	**get_args(char *str)
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
