/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:46:25 by tissad            #+#    #+#             */
/*   Updated: 2024/08/03 00:54:11 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/env/env.h"
#include "../builtins/env/struct_env.h"
#include "parsenv.h"
#include <libft.h>
#include <stdbool.h>

static char	*pars_key(char **cmd)
{
	size_t	len;
	char	*str_cmd;

	len = 0;
	str_cmd = *cmd;
	if (!(str_cmd[len] == '_' || ft_isalpha(str_cmd[len])))
		return (NULL);
	while (str_cmd[len] && !(str_cmd[len] == '=' || (str_cmd[len] == '+'
				&& str_cmd[len + 1] && str_cmd[len + 1] == '=')))
	{
		if (!(str_cmd[len] == '_' || ft_isalnum(str_cmd[len])))
			return (NULL);
		len++;
	}
	*cmd = &str_cmd[len];
	return (ft_substr(str_cmd, 0, len));
}

static int	pars_op(char **cmd)
{
	size_t	len;
	char	*str_cmd;

	len = 0;
	str_cmd = *cmd;
	if (str_cmd[len])
	{
		if (str_cmd[len] == '=')
		{
			*cmd = &str_cmd[len + 1];
			return (EQUAL);
		}
		if (str_cmd[len] == '+' && str_cmd[len + 1] == '=')
		{
			*cmd = &str_cmd[len + 2];
			return (ANDEQUAL);
		}
	}
	return (NOTHING);
}

static char	*pars_value(char **cmd)
{
	char	*str_cmd;

	str_cmd = *cmd;
	if (!str_cmd)
		return (NULL);
	return (ft_substr(str_cmd, 0, ft_strlen(str_cmd) + 1));
}

void	*pars_var(char *str_cmd, char *print_error)
{
	t_var	*var;
	char	*dup_cmd;
	char	*begin;
	char	*key;
	int		op;

	dup_cmd = ft_strdup(str_cmd);
	begin = dup_cmd;
	key = pars_key(&dup_cmd);
	if (!key)
	{
		ft_fprintf(STDERR_FILENO, "%s %s : not a valid identifier\n", \
		print_error, str_cmd);
		free(begin);
		return (NULL);
	}
	op = pars_op(&dup_cmd);
	var = create_var(key, op, pars_value(&dup_cmd));
	free(begin);
	return ((void *)var);
}
