/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:24 by tissad            #+#    #+#             */
/*   Updated: 2024/06/25 14:55:14 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <libft.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/minishell.h"
#include <stdbool.h>

# define MAX_ENV 512

typedef struct s_var
{
    bool    env_flag;
    char    *key;
    char    *value;
}t_var;

typedef struct s_env
{
    t_list  *env_p[MAX_ENV];
    int     nb_var;
}   t_env;


void	ft_env(t_env *env);
void	ft_export(t_env *env, char **args);
void	init_local_env(t_env *local_env, char **envp);

#endif
