/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:52 by nabboud           #+#    #+#             */
/*   Updated: 2024/06/02 13:03:23 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <strings.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <bsd/string.h>
# include <fcntl.h>
# include <signal.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <wait.h>
#include <readline/readline.h>

typedef struct s_signals
{
        int i;
}t_signals;


/**
 * @brief Verifie dans chaque PATH si cmd utilisable.
 * 
 * @param cmd La commade (ex: ls, wc etc).
 * @return Le bon PATH qui contient la cmd.
 */
char *based_path(char *cmd);
char *take_of_double_quote(char *str);
char *take_of_single_quote(char *str);
char *verif_quote(char *str);
void main_signal();
void sig_handler(int sig);


# endif