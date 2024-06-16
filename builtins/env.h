/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:24 by tissad            #+#    #+#             */
/*   Updated: 2024/06/13 15:55:03 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <libft.h>
#include "../lib/libft/includes/libft.h"

# define MAX_ENV 512


typedef struct s_env
{
    t_list  *env_p[MAX_ENV];
    int     nb_var;
}   t_env;

void	ft_env(t_env *env);
void	ft_export(t_env *env, char *env_var);
void	init_local_env(t_env *local_env, char **envp);

#endif
