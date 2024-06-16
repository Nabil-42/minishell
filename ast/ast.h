/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:03:37 by tissad            #+#    #+#             */
/*   Updated: 2024/06/13 15:01:48 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H

# define AST_H

typedef enum
{
	NODE_COMMAND,
	NODE_OPERATOR,
	NODE_GROUP
}					node_type;

// Types d'opérateurs
typedef enum
{
	OP_AND,
	OP_OR,
	OP_PIPE
}					operator_type;

// Nœud de commande
typedef struct s_command
{
	char			**args;
}					t_command;

// Nœud d'opérateur
typedef struct s_operator
{
	operator_type	type;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_operator;

// Nœud de groupe (parenthèses)
typedef struct s_group
{
	struct s_ast	*child;
}					t_group;

// Structure de l'AST
typedef struct s_ast
{
	node_type		type;
	union
	{
		t_command	sh_command;
		t_operator	sh_operator;
		t_group		sh_group;
	} node;
}					t_ast;

#endif