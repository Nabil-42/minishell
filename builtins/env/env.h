/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:24 by tissad            #+#    #+#             */
/*   Updated: 2024/08/08 14:52:01 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "struct_env.h"
/*env_init*/
t_var			*create_var(char *key, int op, char *value);
/*env_clean*/
void			delete_envp(char **envp);
void			delete_var(t_var *var);
void			del(void *content);
/**/
/*export*/
void			add_var(t_env *env, t_var *var);
/*unset*/
/*utils*/
unsigned int	hash_function(const char *key, unsigned int table_size);
t_list			*exist_env_var(char *key, t_list *lst);
#endif
