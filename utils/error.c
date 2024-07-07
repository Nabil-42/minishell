/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 23:04:41 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 11:24:26 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

int	handle_error_1(int saved_stdin, int saved_stdout, t_general *g)
{
	g->flag_eko_n = 0;
	if (saved_stdout < 0 || saved_stdin < 0)
	{
		g->exval = 2;
		return (-1);
	}
	return (0);
}

int	handle_error_2(t_general *g, char *cmd)
{
	if (g->tab_cmd[0] == NULL)
	{
		g->exval = 2;
		return (-1);
	}
	if (ft_strcmp(g->tab_cmd[0], "''") == 0 || ft_strcmp(g->tab_cmd[0],
			"\"\"") == 0)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", cmd);
		g->exval = 126;
		return (-1);
	}
	return (0);
}

void	handle_error_3_5(t_general *g, int *i)
{
	if (g->tab_cmd[*i + 1] != NULL)
	{
		if (ft_strncmp(g->tab_cmd[*i + 1], " ./", 3) == 0)
		{
			g->tab_file[*i + 1] = ft_strdup(g->tab_cmd[*i + 1] + 1);
			g->nbr_file += 1;
		}
	}
}

void	handle_error_3_bis(t_general *g, int *fd, int *i, char *buff)
{
	if (is_space_bis(g->tab_file[*i + 1]))
		*fd = handle_single_redirection((g->tab_file[*i + 1]), g->tab_dir[*i],
				g);
	else
	{
		buff = verif_quote((g->tab_file[*i + 1]));
		*fd = handle_single_redirection(buff, g->tab_dir[*i], g);
		free(buff);
	}
	g->nbr_file -= 1;
}

void	handle_error_3(t_general *g, int *fd, int *i)
{
	char	*buff;

	buff = NULL;
	handle_error_3_5(g, i);
	if (g->nbr_file > g->nbr_dir)
	{
		handle_error_3_bis(g, fd, i, buff);
	}
	else
	{
		if (is_space_bis(g->tab_file[*i]))
		{
			free(g->tab_cmd[1]);
			g->tab_cmd[1] = NULL;
			buff = verif_quote_bis(g->tab_file[*i]);
			*fd = handle_single_redirection(buff, g->tab_dir[*i], g);
			free(buff);
		}
		else
		{
			buff = verif_quote(g->tab_file[*i]);
			*fd = handle_single_redirection(buff, g->tab_dir[*i], g);
			free(buff);
		}
	}
}
