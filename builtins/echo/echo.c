/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/07/13 18:16:53 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

#define PATH_MAX 4096

char	*remake_str_bis(char **tab)
{
	int		j;
	int		k;
	int		i;
	char	*new_str;

	i = 0;
	if (tab[0] == NULL)
		return (NULL);
	new_str = malloc(sizeof(char) * PATH_MAX + 1);
	if (new_str == NULL)
		return (NULL);
	k = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j])
		{
			new_str[k] = tab[i][j];
			++k;
			++j;
		}
		if (tab[i + 1] != NULL)
			new_str[k] = ' ';
		++k;
		++i;
	}
	k--;
	new_str[k] = '\0';
	return (new_str);
}

char	*remake_str(char **tab, t_echo *eko, int i)
{
	int		j;
	int		k;
	char	*new_str;

	if (tab[i] == NULL)
		return (NULL);
	new_str = malloc(sizeof(char) * eko->len_str + 1);
	if (new_str == NULL)
		return (NULL);
	k = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			new_str[k] = tab[i][j];
			++k;
			++j;
		}
		if (tab[i + 1] != NULL)
			new_str[k] = ' ';
		++k;
		++i;
	}
	k--;
	new_str[k] = '\0';
	return (new_str);
}

void	echo_2(t_general *g, char *str, t_echo *eko, char *tmp)
{
	(void)g;
	if (eko->tab[1] && ft_strcmp(eko->tab[1], "-n") == 0)
	{
		echo_args(str, eko, tmp, g);
		g->flag_eko_n = 1;
		free(str);
		return ;
	}
	if (*tmp == '\0' && str[0] != 39 && str[1] != 39
		&& str[0] != '"' && str[1] != '"')
	{
		dollar(str, eko, g);
		free(str);
		return ;
	}
	free(str);
}

void	echo(char **tab, t_echo *eko, t_general *g)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	if (tab[1] && ft_strcmp(tab[1], "-n") == 0)
		str = remake_str(tab, eko, 2);
	else
		(str = remake_str(tab, eko, 1));
	if (!str)
	{
		g->flag_eko_n = 10;
		free_tab(tab);
		free(str);
		return ;
	}
	eko->line = malloc(sizeof(char) * (eko->len_str + PATH_MAX + 1));
	if (!eko->line)
		return (free(str), (void)0);
	tmp = echo_verif_quote(str, eko, g);
	if (tmp == NULL)
	{
		g->flag_eko_n = 11;
		free(eko->line);
		free(str);
		return ;
	}
	echo_2(g, str, eko, tmp);
	g->handle_eko = eko->line;

}

void	echo_2_bis(t_general *g, char *str, t_echo *eko, char *tmp)
{
	(void)g;
	if (*tmp == '\0' && str[0] != 39 && str[1] != 39)
	{
		dollar_bis(str, eko, g);
		free(str);
		return ;
	}
	free(str);
}

void	echo_bis(char **tab, t_echo *eko, t_general *g)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	init_eko(eko, g);
	str = remake_str(tab, eko, 0);
	if (!str)
	{
		free_tab(tab);
		free(str);
		return ;
	}
	eko->line = malloc(sizeof(char) * (eko->len_str + PATH_MAX + 1));
	if (!eko->line)
		return (free(str), (void)0);
	tmp = echo_verif_quote(str, eko, g);
	if (tmp == NULL)
	{
		free(str);
		return ;
	}
	echo_2_bis(g, str, eko, tmp);
}
