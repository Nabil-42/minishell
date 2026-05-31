/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsenv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:44:16 by tissad            #+#    #+#             */
/*   Updated: 2024/08/03 00:37:31 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSENV_H
# define PARSENV_H

# define EQUAL 1
# define ANDEQUAL 2
# define NOTHING 0

void	*pars_var(char *str_cmd, char *print_error);
char	**get_args(char *str);

#endif