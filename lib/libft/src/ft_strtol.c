/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:33:26 by tissad            #+#    #+#             */
/*   Updated: 2024/05/03 12:22:06 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

/*dans ce fichier les fonction pour ecrire un futur strtol
 * il manque deux plusieurs
 * travailler sur des long
 * ajouter les bases
 * renvoyer pointeur au dernier caractere non convrtable, au lieu de dernier
 * de la chaine
 * */
static const char	*avoid_whitespace(const char *str)
{
	while ((*str == ' ') || (*str >= '\t' && *str <= '\r'))
		str++;
	return (str);
}

static const char	*is_negative(const char *str, int *sig)
{
	*sig = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sig *= -1;
		str++;
	}
	return (str);
}

static const char	*is_overflow_detec(\
const char *str, char *min, char *max, int sig)
{
	int		len;
	int		len_max;

	while (*str == '0')
		str++;
	if (*str == '\0')
		str--;
	len = ft_strlen(str);
	if (len == 0 && sig == -1)
		return (str - 1);
	len_max = ft_strlen(max);
	if (len > len_max)
		return (&str[len_max - 1]);
	else if (len == len_max)
	{
		if (sig == -1 && (((int)ft_strcmp(str, min + 1)) > 0))
			return (&str[len_max - 1]);
		else if (sig == 1 && (((int)ft_strcmp(str, max)) > 0))
			return (&str[len_max - 1]);
	}
	return (NULL);
}

static const char	*is_overflow(const char *str, int sig)
{
	char		*max;
	char		*min;
	const char	*endptr;

	max = ft_itoa(INT_MAX);
	min = ft_itoa(INT_MIN);
	endptr = is_overflow_detec(str, min, max, sig);
	free(max);
	free(min);
	return (endptr);
}

/*add base*/
int	ft_strtoi(const char *str, char **endptr)
{
	int	nb;
	int	sig;

	nb = 0;
	str = avoid_whitespace(str);
	str = is_negative(str, &sig);
	*endptr = (char *)is_overflow(str, sig);
	if (sig == -1 && *endptr)
		return (INT_MIN);
	if (sig == 1 && *endptr)
		return (INT_MAX);
	while (ft_isdigit(*str))
	{
		nb = nb * 10 + (int)(*str - '0');
		str++;
	}
	if (*str)
		*endptr = (char *)str;
	return (nb * sig);
}
