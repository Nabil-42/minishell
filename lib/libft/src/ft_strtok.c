/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <issad.tahar@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:03:59 by tissad            #+#    #+#             */
/*   Updated: 2024/03/05 10:29:51 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline char	*init_token_start(char *str, char *last_token_end)
{
	char	*token_start;

	if (str != NULL)
		token_start = str;
	else
		token_start = last_token_end;
	return (token_start);
}

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*last_token_end = NULL;
	char		*token_start;
	char		*token_end;

	token_start = init_token_start(str, last_token_end);
	if (!token_start)
		return (NULL);
	token_start += ft_strspn(token_start, delimiters);
	if (*token_start == '\0')
	{
		last_token_end = NULL;
		return (NULL);
	}
	token_end = token_start + ft_strcspn(token_start, delimiters);
	if (*token_end != '\0')
	{
		*token_end = '\0';
		last_token_end = token_end + 1;
	}
	else
		last_token_end = NULL;
	return (token_start);
}
