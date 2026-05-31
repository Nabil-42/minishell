/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:17:26 by tissad            #+#    #+#             */
/*   Updated: 2024/08/11 21:45:02 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/parsenv.h"
#include "env.h"
#include "minishell.h"

static void	ft_print_export(t_env *env);
static void	rest_value(t_var *var, char *new_value);
static void	join_value(t_var *var, char *new_value);

char	**expand_export(t_general *g, t_echo *eko, char **args)
{
	int		i;
	char	*tmp;
	char	**expand_args;

	tmp = remake_str(args, eko, 0);
	expand_args = ft_split_quote(tmp);
	free(tmp);
	i = 0;
	while (expand_args[i])
	{
		tmp = expand_hd(expand_args[i], g);
		expand_args[i] = tmp;
		i++;
	}
	return (expand_args);
}

void	ft_export(t_general *g, t_echo *eko, char **args)
{
	int		i;
	t_var	*var;
	char	**expand_args;

	g->flag_eko_n = 3;
	if (ft_strncmp("export", args[0], 6) == 0 && ft_strlen(args[0]) > 6)
		return ;
	expand_args = expand_export(g, eko, args);
	i = 1;
	if (!expand_args[i])
		return (ft_print_export(&g->local_env), (void)0);
	while (expand_args[i])
	{
		var = (t_var *)pars_var(expand_args[i], "minishell: export:");
		if (!var)
		{
			i++;
			g->exval = EXIT_FAILURE;
			continue ;
		}
		add_var(&g->local_env, var);
		i++;
	}
	free_tab(expand_args);
}

static void	ft_print_export(t_env *env)
{
	t_list	*lst_iter;
	t_var	*var;
	int		i;

	i = 0;
	while (i < MAX_ENV)
	{
		lst_iter = env->env_p[i];
		while (lst_iter)
		{
			var = (t_var *)(lst_iter->content);
			printf("export %s=\"%s\"\n", var->key, var->value);
			lst_iter = lst_iter->next;
		}
		i++;
	}
}

void	add_var(t_env *env, t_var *var)
{
	t_list	*new;
	t_list	*elt;
	int		hash;

	hash = hash_function(var->key, MAX_ENV);
	elt = exist_env_var(var->key, env->env_p[hash]);
	if (!elt)
	{
		new = ft_lstnew((void *)var);
		ft_lstadd_back(&env->env_p[hash], new);
		env->nb_var++;
	}
	else
	{
		if (var->op == ANDEQUAL)
			join_value((t_var *)elt->content, var->value);
		else if (var->op == EQUAL)
			rest_value((t_var *)elt->content, var->value);
		delete_var(var);
	}
}

static void	rest_value(t_var *var, char *new_value)
{
	free(var->value);
	var->value = ft_strdup(new_value);
}

static void	join_value(t_var *var, char *new_value)
{
	char	*tmp;

	tmp = var->value;
	var->value = ft_strjoin(tmp, new_value);
	free(tmp);
}
