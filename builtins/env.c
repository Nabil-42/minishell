/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:17:26 by tissad            #+#    #+#             */
/*   Updated: 2024/06/13 16:22:06 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

unsigned int hash_function(const char *key, unsigned int table_size)
{
    uint32_t hash;
    const uint32_t fnv_prime = 16777619U;
    
	hash = 2166136261U;
	while (*key)
	{
        hash ^= (uint8_t)*key++;
        hash *= fnv_prime;
    }
    return (hash % table_size);
}

char	*get_key(char *env_var)
{
	size_t	len;

	len = 0;
	while (env_var[len] && env_var[len] != '=')
	{
		len++;
	}
	return (ft_substr(env_var, 0, len));
}

void	dup_env(t_env *local_env, char **envp)
{
	t_list	*new_var;
	char	*key;
	int		hash;
	int		i;

	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i]);
		hash = hash_function(key, MAX_ENV);
		new_var = ft_lstnew((void *)ft_strdup(envp[i]));
		ft_lstadd_back(&local_env->env_p[hash], new_var);
		free(key);
		local_env->nb_var++;
		i++;
	}
}

void	init_local_env(t_env *local_env, char **envp)
{
	int	i;

	i = 0;
	while (i < MAX_ENV)
	{
		local_env->env_p[i] = NULL;
		i++;
	}
	local_env->nb_var = 0;
	dup_env(local_env, envp);
}



char **get_local_env(t_env *env)
{
	char	**local_env;
	t_list	*lst_iter;
	int		i;
	int		j;

	local_env = malloc(sizeof(void *) * (env->nb_var + 1));
	if (!local_env)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (i < MAX_ENV)
	{
		lst_iter = env->env_p[i];
		while (lst_iter)
		{
			local_env[j] = (char *)lst_iter->content;
			lst_iter = lst_iter->next;
			j++;
		}
		i++;
	}
	local_env[j] = NULL;
	return (local_env);
}

void	del(void *content)
{
	free(content);
}

int		cond(void *value, void *content)
{
	return (ft_strncmp(value, content, ft_strlen(value)));
}

void	delete_envp(t_env *env)
{
	int		i;
	
	i = 0;
	while (i < MAX_ENV)
	{
		ft_lstclear(&env->env_p[i], del);
		i++;
	}	
}

int	exist_env_var(char *env_var, char *key, t_list *lst)
{
	t_list *lst_iter;
	
	lst_iter = lst;
	while (lst_iter)
	{
		if (ft_strncmp(key, lst_iter->content, ft_strlen(key)) == 0)
		{
			free(lst_iter->content);
			lst_iter->content = ft_strdup(env_var);
			return (1);
		}
		lst_iter = lst_iter->next;
	}
	return (0);
}

void	ft_export(t_env *env, char *env_var)
{
	t_list	*new_var;
	char	*key;
	int		hash;

	key = get_key(env_var);
	hash = hash_function(key, MAX_ENV);
	if (!env->env_p[hash])
	{
		new_var = ft_lstnew((void *)ft_strdup(env_var));
		ft_lstadd_back(&env->env_p[hash], new_var);
		env->nb_var++;
	}
	else
	{
		if(!exist_env_var(env_var, key, env->env_p[hash]))
		{
			new_var = ft_lstnew((void *)ft_strdup(env_var));
			ft_lstadd_back(&env->env_p[hash], new_var);
			env->nb_var++;	
		}
	}
	free(key);
}

void	ft_unset(t_env *env, char *key)
{
	t_list	**lst;
	int		hash;

	hash = hash_function(key, MAX_ENV);
	lst = &env->env_p[hash];
	ft_lstdelcond(lst, key, cond, del);
}

void	ft_env(t_env *env)
{
	char	**local_env;
	int		i;

	local_env = get_local_env(env);
	i = 0;
	while (local_env[i])
	{
		if (local_env[i])
			printf("%s\n", local_env[i]);

		i++;
	}
	free(local_env);
}

// int	main(int ac, char **av, char **envp)
// {
// 	(void) ac;
// 	(void) av;
// 	(void) envp;
// 	t_env env;
	
// 	init_local_env(&env);
// 	dup_env(&env, envp);
// 	ft_export(&env, "VAR=roroooooooooooooo");
// 	ft_env(&env);
// 	ft_export(&env, "TOTO=111");
// 	ft_export(&env, "TITI=111");
// 	ft_export(&env, "TUTU=111");
// 	ft_export(&env, "VAR=11111111111111111111111111111111111111111");
// 	ft_export(&env, "VAR=0");
// 	ft_env(&env);
// 	ft_unset(&env, "VAR");
// 	ft_env(&env);	
// 	delete_envp(&env);
// }