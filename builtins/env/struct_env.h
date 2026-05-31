/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:21:45 by tissad            #+#    #+#             */
/*   Updated: 2024/07/30 16:34:23 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_ENV_H
# define STRUCT_ENV_H

# define MAX_ENV 512
# include <libft.h>
# include <stdbool.h>

typedef struct s_var
{
	bool	env_flag;
	char	*key;
	char	*value;
	int		op;
}			t_var;

typedef struct s_env
{
	t_list	*env_p[MAX_ENV];
	int		nb_var;
}			t_env;

#endif