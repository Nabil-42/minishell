/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:09:46 by nabboud           #+#    #+#             */
/*   Updated: 2024/06/20 18:02:53 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"

void	free_tokens(char **tokens, int num_tokens)
{
	int	i;

	i = 0;
	while (i < num_tokens)
	{
		free(tokens[i]);
		++i;
	}
	free(tokens);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	**split_str(char *str, int *result_size)
{
	char	**result;
	int		len;
	int		in_quotes;
	int		start;
	int		i;
	int		part_len;
	char	*part;
	int		part_len;
	char	*part;

	result = malloc(PATH_MAX * sizeof(char *));
	*result_size = 0;
	if (!result)
	{
		// Gérer l'erreur d'allocation mémoire si nécessaire
		return (NULL);
	}
	len = strlen(str);
	in_quotes = 0;
	start = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
		{
			if (in_quotes == 1)
				in_quotes = 0;
			else if (in_quotes == 0)
				in_quotes = 1;
		}
		else if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
		{
			if (in_quotes == 2)
				in_quotes = 0;
			else if (in_quotes == 0)
				in_quotes = 2;
		}
		if (!in_quotes && is_delimiter(str[i]))
		{
			if (start < i)
			{
				part_len = i - start;
				part = malloc(part_len + 1);
				if (!part)
				{
					// Gérer l'erreur d'allocation mémoire si nécessaire
					return (NULL);
				}
				strncpy(part, str + start, part_len);
				part[part_len] = '\0';
				result[*result_size] = part;
				(*result_size)++;
			}
			start = i + 1;
		}
		i++;
	}
	if (start < len)
	{
		part_len = len - start;
		part = malloc(part_len + 1);
		if (!part)
		{
			// Gérer l'erreur d'allocation mémoire si nécessaire
			return (NULL);
		}
		strncpy(part, str + start, part_len);
		part[part_len] = '\0';
		result[*result_size] = part;
		(*result_size)++;
	}
	result[*result_size] = NULL; // Terminer le tableau avec NULL
	return (result);
}

// Fonction pour vérifier si deux caractères forment un délimiteur de redirection ">>" ou "<<"
char	**split_delimiters(const char *str, int *result_size)
{
	int		len;
	int		delimiter_count;
	int		i;
	char	**result;

	len = strlen(str);
	int in_quotes = 0; // 0: pas de guillemets, 1: guillemets simples,
		2: guillemets doubles
	delimiter_count = 0;
	// Première passe : compter les délimiteurs
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
		{
			in_quotes = (in_quotes == 1) ? 0 : 1;
		}
		else if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
		{
			in_quotes = (in_quotes == 2) ? 0 : 2;
		}
		if (!in_quotes && is_delimiter(str[i]))
		{
			delimiter_count++;
			if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
					+ 1] == '<'))
			{
				i++;
			}
		}
		i++;
	}
	result = malloc((delimiter_count + 1) * sizeof(char *));
	if (!result)
	{
		return (NULL);
	}
	*result_size = 0;
	// Deuxième passe : remplir les délimiteurs
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
		{
			in_quotes = (in_quotes == 1) ? 0 : 1;
		}
		else if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
		{
			in_quotes = (in_quotes == 2) ? 0 : 2;
		}
		if (!in_quotes && is_delimiter(str[i]))
		{
			if (i + 1 < len && str[i] == '>' && str[i + 1] == '>')
			{
				result[*result_size] = malloc(3);
				if (!result[*result_size])
				{
					free_tab(result);
					return (NULL);
				}
				result[*result_size][0] = '>';
				result[*result_size][1] = '>';
				result[*result_size][2] = '\0';
				(*result_size)++;
				i++;
			}
			else if (i + 1 < len && str[i] == '<' && str[i + 1] == '<')
			{
				result[*result_size] = malloc(3);
				if (!result[*result_size])
				{
					free_tab(result);
					return (NULL);
				}
				result[*result_size][0] = '<';
				result[*result_size][1] = '<';
				result[*result_size][2] = '\0';
				(*result_size)++;
				i++;
			}
			else
			{
				result[*result_size] = malloc(2);
				if (!result[*result_size])
				{
					free_tab(result);
					return (NULL);
				}
				result[*result_size][0] = str[i];
				result[*result_size][1] = '\0';
				(*result_size)++;
			}
		}
		i++;
	}
	result[*result_size] = NULL; // Terminer le tableau avec NULL
	return (result);
}
