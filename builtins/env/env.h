/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:24 by tissad            #+#    #+#             */
/*   Updated: 2024/06/23 09:48:29 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <libft.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/minishell.h"

# define MAX_ENV 512


typedef struct s_env
{
    t_list  *env_p[MAX_ENV];
    int     nb_var;
}   t_env;


unsigned int hash_function(const char *key, unsigned int table_size);
char	*get_key(char *env_var);
void	dup_env(t_env *local_env, char **envp);
void	del(void *content);
char **get_local_env(t_env *env);
void	init_local_env(t_env *local_env, char **envp);
void	ft_env(t_env *env);
void	ft_unset(t_env *env, char *key);
void	ft_export(t_env *env, char *env_var);
int	exist_env_var(char *env_var, char *key, t_list *lst);
void	delete_envp(t_env *env);
void	ft_env(t_env *env);
void	ft_export(t_env *env, char *env_var);
void	init_local_env(t_env *local_env, char **envp);

#endif
