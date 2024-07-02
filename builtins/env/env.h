/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:24 by tissad            #+#    #+#             */
/*   Updated: 2024/07/03 00:03:03 by nabil            ###   ########.fr       */
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


// void	ft_env(t_env *env, t_general *g);

void	init_local_env(t_env *local_env, char **envp);
void	delete_env(t_env *env);
char	**get_local_env(t_env *env);
void	ft_add_var(t_env *env, char *env_str, bool flag);
// void	ft_unset(t_env *env, char **args, t_general *g);
char	*ft_getenv(t_env *env, char *key);

#endif
