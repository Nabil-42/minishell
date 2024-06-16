/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:03:20 by tissad            #+#    #+#             */
/*   Updated: 2024/06/11 17:46:55 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// Fonction pour créer un nœud de commande
t_ast	*create_command_node(char **args)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (0);
	node->type = NODE_COMMAND;
	node->node.sh_command.args = args;
	return (node);
}

// Fonction pour créer un nœud d'opérateur
t_ast	*create_operator_node(operator_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (0);
	node->type = NODE_OPERATOR;
	node->node.sh_operator.type = type;
	node->node.sh_operator.left = left;
	node->node.sh_operator.right = right;
	return (node);
}

// Fonction pour créer un nœud de groupe
t_ast	*create_group_node(t_ast *child)
{
	t_ast *node = malloc(sizeof(t_ast));
	if (!node)
		return (0);
	node->type = NODE_GROUP;
	node->node.sh_group.child = child;
	return (node);
}
