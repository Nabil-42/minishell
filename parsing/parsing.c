/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:09:46 by nabboud           #+#    #+#             */
/*   Updated: 2024/06/02 21:11:12 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../lib/libft/includes/libft.h"

char *take_of_double_quote(char *str)
{
	int i;
	int j;
	char *new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!new_str)
		return NULL;
	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (str[i + j] == '"')
			++j;
		new_str[i] = str[i + j];
		++i;
	}
	new_str[i] = '\0';
	
	return new_str;
}
char *take_of_single_quote(char *str)
{
	int i;
	int j;
	char *new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!new_str)
		return NULL;
	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (str[i + j] == 39)
			++j;
		new_str[i] = str[i + j];
		++i;
	}
	new_str[i] = '\0';
	
	return new_str;
}

char *verif_quote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			while(str[i])
			{
				++i;
				if (str[i] == '"')
					return (take_of_double_quote(str));
			}
			return (printf("minishell: %s: command not found\n", str), exit(127), NULL);
		}
		if (str[i] == 39)
		{
			while(str[i])
			{
				++i;
				if (str[i] == 39)
					return (take_of_single_quote(str));
			}
			return (printf("minishell: %s: command not found\n", str), exit(127), NULL);
		}
		++i;
	}
	return(str);
}

