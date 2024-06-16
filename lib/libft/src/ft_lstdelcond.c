/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelcond.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:39:50 by tissad            #+#    #+#             */
/*   Updated: 2024/06/07 11:50:45 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstdelcond(t_list **lst, void *value, int (*cond)(void*, void*), \
void (*del)(void*))
{
	t_list	*current;
	t_list	*previous;

	if (*lst == NULL)
		return ;
	current = *lst;
	previous = NULL;
	while (current != NULL)
	{
		if (cond(value, current->content) == 0)
		{
			if (previous != NULL)
				previous->next = current->next;
			else
				*lst = current->next;
			ft_lstdelone(current, del);
			return ;
		}
		previous = current;
		current = current->next;
	}
}
