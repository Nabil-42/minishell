/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:52 by nabboud           #+#    #+#             */
/*   Updated: 2024/06/15 16:46:11 by nabil            ###   ########.fr       */
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
#include "../lib/libft/includes/libft.h"
#include "../builtins/env.h"
#define PATH_MAX 4096

typedef struct s_general
{
        char **tab_cmd;
        char *line;
        char *prompt;
        int status;
        char *command_before_pipe;
        char *command_after_pipe;
        int count;
        int nbr_token;
        
}t_general;

typedef struct s_echo
{
        int len_str;
        int flag_double;
        int flag_simple;
        char *line;
        int flag_print;
        int i;
        int j;
        int $;
}t_echo;

typedef struct s_signals
{
        int i;
}t_signals;

int is_delimiter(char c);
int count_tokens(char *str);
char **split_str(char *str, int *num_tokens);
void count_commands(char *command_line, t_general *g);
int check_redirections(char *str);
int check_special_characters(const char *str);
char *based_path(char *cmd);
char *verif_quote(char *str);
void main_signal();
void sig_handler(int sig);
void pipe_while(t_general *g);
void	ft_execve(char *line, char *tab_cmd);
int builtin(char *line, t_env * local_env);
void cd_project(char **tab, t_env *local_env);
void pwd(char **tab);
void export(char **tab);
int dollar_double(char *str, t_echo *eko);
int echo_take_of_double_quote(char *str, t_echo *eko, int n);
int dollar(char *str, t_echo *eko);
int dollar_n(char *str, t_echo *eko);
int echo_take_of_simple_quote(char *str, t_echo *eko, int n);
int direction_double(char *str, int i, t_echo *eko);
int direction(char *str, int i, t_echo *eko);


# endif