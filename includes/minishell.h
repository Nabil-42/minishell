/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:52 by nabboud           #+#    #+#             */
/*   Updated: 2024/06/19 22:09:41 by nabil            ###   ########.fr       */
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
#include "../builtins/env/env.h"

#define PATH_MAX 4096

typedef struct s_general
{
        char **tab_cmd;
        char **tab_dir;
        char *line;
        char *prompt;
        int status;
        char *command_before_pipe;
        char *command_after_pipe;
        int count;
        int nbr_token;
        int $;
        
}t_general;

typedef struct s_echo
{
        int flag;
        int flag_i;
        int dir;
        char *line;
        int len_str;
        int i;
        int j;
        int $;
}t_echo;

typedef struct s_signals
{
        int i;
}t_signals;

///////////////////// ECHO ////////////////////////

int echo_take_of_simple_quote(char *str, t_echo *eko, int n);
char *remake_str(char **tab, t_echo *eko, int i);
void prepare_echo(char **tab, t_echo *eko, char **str, char **tmp);
void execute_echo(char **tab, t_echo *eko, char *str, char *tmp);
void finalize_echo(char **tab, t_echo *eko, char *tmp, char *str);
void echo(char **tab, t_echo *eko);
int handle_consecutive_quotes(char *str, t_echo *eko);
int handle_single_double_quote(char *str, t_echo *eko, int *flag);
void copy_non_special_char(char *str, t_echo *eko);
int echo_take_of_double_quote(char *str, t_echo *eko, int n);
void echo_args(char *str, t_echo *eko, char **tab, char *tmp);
int handle_double_quote(char *str, t_echo *eko, int *i, int *test);
int handle_single_quote(char *str, t_echo *eko, int *i, int *test);
char *echo_verif_quote(char *str, t_echo *eko);
char *handle_remaining_chars(char *str, t_echo *eko, int test);
int process_single_quotes(char *str, t_echo *eko, int *i, int *test);
int process_double_quotes(char *str, t_echo *eko, int *i, int *test);


///////////////////// ENV ///////////////////////////

int	cond(void *value, void *content);
void	ft_env(t_env *env);
void	ft_unset(t_env *env, char *key);
void	ft_export(t_env *env, char *env_var);
int	exist_env_var(char *env_var, char *key, t_list *lst);
void	delete_envp(t_env *env);
unsigned int hash_function(const char *key, unsigned int table_size);
char	*get_key(char *env_var);
void	dup_env(t_env *local_env, char **envp);
void	init_local_env(t_env *local_env, char **envp);
char **get_local_env(t_env *env);
void	del(void *content);

///////////////////// REDIRECTION ///////////////////////////
void skip_white_space(char *str, int i, char *output);


///////////////////// PARSING ///////////////////////////
int check_special_characters(const char *str);
void count_commands(char *command_line, t_general *g);
int is_delimiter(char c);
int count_tokens(char *str);
char *ft_strncpy(char *dest, const char *src, size_t n);
int verif_quote_2(char *str, int i, int *double_quote_count, int *single_quote_count);
char *verif_quote(char *str);
int is_redirection(char c);
void check_redirection_2(int *expecting_command, int *i, char *str);
int is_space(char *str, int *i);
int check_redirections(char *str);
char **split_delimiters(const char *str, int *result_size);






///////////////////// BUILTINS ///////////////////////////
void ft_exit(char **tab, t_general *g);





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
int builtin(char *line, t_env * local_env, t_general *g);
void cd_project(char **tab, t_env *local_env, t_general *g);
void pwd(char **tab);
void export(char **tab);
int dollar_double(char *str, t_echo *eko);
int echo_take_of_double_quote(char *str, t_echo *eko, int n);
int dollar(char *str, t_echo *eko);
int dollar_n(char *str, t_echo *eko);
int direction_double(char *str, int i, t_echo *eko);
int direction(char *str, int i, t_echo *eko);


# endif