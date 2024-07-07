/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:04:32 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 11:36:06 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

char	*trim_space(char *str)
{
	char	*new_start;
	char	*new_str;

	if (str == NULL)
	{
		return (NULL);
	}
	new_start = str;
	while (*new_start && *new_start <= 32)
	{
		new_start++;
	}
	new_str = ft_strdup(new_start);
	if (new_str == NULL)
	{
		return (NULL);
	}
	return (new_str);
}
