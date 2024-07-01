/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:17:26 by tissad            #+#    #+#             */
/*   Updated: 2024/07/01 19:30:39 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		len++;
	return (ft_substr(env_var, 0, len));
}
char	*get_value(char *env_var)
{
	size_t	len;

	len = 0;
	while (env_var[len] && env_var[len] != '=')
		len++;
	len++; 
	return (ft_substr(env_var, len, ft_strlen(env_var) - len));
}

t_var	*create_var(char *key, char *value, bool env_flag)
{
	t_var	*var;
	
	var = malloc(sizeof(t_var) * 1);
	if (!var)
		return (NULL);
	var->env_flag = env_flag;
	var->key = key;
	var->value = value;
	return (var);	
}

void	delete_var(t_var *var)
{
	free(var->key);
	free(var->value);
}

void	rest_value(t_var *var, char *new_value)
{
	free(var->value);
	var->value = new_value;
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
		new_var = ft_lstnew((void *) \
		create_var(key, get_value(envp[i]), true));
		ft_lstadd_back(&local_env->env_p[hash], new_var);
		local_env->nb_var++;
		i++;
	}
}

void	init_local_env(t_env *local_env, char **envp)
{
	int	i;

	(void)envp;
	i = 0;
	while (i < MAX_ENV)
	{
		local_env->env_p[i] = NULL;
		i++;
	}
	local_env->nb_var = 0;
	dup_env(local_env, envp);
}

char	*tvar_to_str(t_var *var)
{
	char	*str;
	char	*tmp;

	tmp	= ft_strjoin(var->key, "=");
	str = ft_strjoin(tmp, var->value);
	free(tmp);
	return (str);
}

char **get_local_env(t_env *env)
{
	t_list	*lst_iter;
	t_var	*var;
	char	**local_env;
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
			var = (t_var *)(lst_iter->content);
			if (var->env_flag)
				local_env[j++] = tvar_to_str(var);
			lst_iter = lst_iter->next;
		}
		i++;
	}
	local_env[j] = NULL;
	return (local_env);
}

void	del(void *content)
{
	t_var	*var;

	var = (t_var *) content;
	delete_var(var);
	free(content);
	content = NULL;
}

int		cond(void *key, void *content)
{
	t_var	*var;
	
	var = (t_var *) content;
	return (var->env_flag && ft_strncmp(key, var->key, ft_strlen(key)));
}

void	delete_env(t_env *env)
{
	int		i;
	
	i = 0;
	while (i < MAX_ENV)
	{
		ft_lstclear(&env->env_p[i], del);
		i++;
	}	
}

t_list	*exist_env_var(char *key, t_list *lst)
{
	t_list	*lst_iter;
	t_var	*var;
	
	lst_iter = lst;
	while (lst_iter)
	{
		var = (t_var *) lst_iter->content;
		if (ft_strncmp(key, var->key, ft_strlen(key)) == 0)
			return (lst_iter);
		lst_iter = lst_iter->next;
	}
	return (lst_iter);
}

void	ft_add_var(t_env *env, char *env_str, bool flag)
{
	t_list	*new;
	t_list	*elt;
	char	*value;
	char	*key;
	int		hash;

	key = get_key(env_str);
	value = get_value(env_str);
	hash = hash_function(key, MAX_ENV);
	elt = exist_env_var(key, env->env_p[hash]);
	if(!elt)
	{
		new = ft_lstnew((void *) create_var(key, value, flag));
		ft_lstadd_back(&env->env_p[hash], new);
	}
	else
	{
		rest_value((t_var *)elt->content, value);
		free(key);
	}
}

void	ft_export(t_general *g, char **args, t_echo *eko)
{
	int	i;

	echo(args, eko, g);
	free_tab(args);
	args = ft_split(eko->line, ' ');
	free(eko->line);
	i = 0;
	while (args[i])
	{
		ft_add_var(&g->local_env, args[i], true);
		g->local_env.nb_var++;	
		i++;
	}
}

void	ft_unset(t_env *env, char **args)
{
	t_list	**lst;
	int		hash;
	int		i;

	//parsing function
	i = 1;
	while (args[i])
	{	
		hash = hash_function(args[i], MAX_ENV);
		lst = &env->env_p[hash];
		ft_lstdelcond(lst, args[i], cond, del);
		env->nb_var--;
		i++;
	}
}

void	delete_envp(char **envp)
{
	while (*envp)
	{
		free(*envp);
		envp++;
	}
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
	delete_envp(local_env);
	free(local_env);
}

char	*ft_getenv(t_env *env, char *key)
{
	t_list	*lst_iter;
	t_var	*var;
	int		hash;
	
	hash = hash_function(key, MAX_ENV);
	lst_iter = env->env_p[hash];
	while (lst_iter)
	{
		var = (t_var *)(lst_iter->content);
		if (var->env_flag && ft_strcmp(key, var->key) == 0)
		{
			return (var->value);		
		}
		lst_iter = lst_iter->next;
	}
	return (NULL);
}

