/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:20:23 by nabboud           #+#    #+#             */
/*   Updated: 2024/08/11 22:06:47 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

void	echo_2_herdoc(t_general *g, char *str, t_echo *eko, char *tmp)
{
	(void)g;
	if (*tmp == '\0' && str[0] != 39 && str[1] != 39 && str[0] != '"'
		&& str[1] != '"')
	{
		dollar(str, eko, g);
		free(str);
		str = NULL;
		return ;
	}
	free(str);
}

void	echo_herdoc(char *str, t_echo *eko, t_general *g)
{
	char	*tmp;

	tmp = NULL;
	if (!str)
		return ;
	if (eko->line)
		free(eko->line);
	eko->line = malloc(sizeof(char) * (eko->len_str + PATH_MAX + 1));
	if (!eko->line)
		return (free(str), (void)0);
	tmp = echo_verif_quote(str, eko, g);
	if (tmp == NULL)
		return ((g->flag_eko_n = 11), free(eko->line), free(str));
	echo_2_herdoc(g, str, eko, tmp);
	if (g->handle_eko)
		free(g->handle_eko);
	g->handle_eko = ft_strdup(eko->line);
	free(eko->line);
	eko->line = NULL;
}
