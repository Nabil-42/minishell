/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:52 by nabboud           #+#    #+#             */
/*   Updated: 2024/07/13 15:52:45 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../builtins/env/env.h"
# include "../lib/libft/includes/libft.h"
# include <bsd/string.h>
# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <limits.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/time.h>
# include <unistd.h>
# include <wait.h>

# define PATH_MAX 4096

typedef struct s_echo
{
	int		flag;
	int		flag_i;
	int		dir;
	char	*line;
	int		len_str;
	int		i;
	int		j;
	int		exval;
	char	**tab;

}			t_echo;

typedef struct s_general
{
	char	**petit_tab;
	char	**tab_cmd;
	char	**tab_dir;
	char	**tab_pipe;
	char	**tab_file;
	char	*line;
	char	*prompt;
	char	*handle_eko;
	char	*command_before_pipe;
	char	*command_after_pipe;
	char	*path;
	char	*handle_ikou;
	int		flag_eko_n;
	int		status;
	int		count;
	int		nbr_dir;
	int		exval;
	int		index_dir;
	int		nbr_pipe;
	int		check_dir;
	int		check_pipe;
	int		nbr_file;
	int		flag_error;

	int		k_pipe;
	int		i_pipe;
	int		received_value;
	int 	prev_pipe_read;
	
	int		i_based_p;

	int		i_right;

	int		split_in_single_quotes;
	int		split_in_double_quotes;
	int		split_start;
	int		split_redirection_found;
	char	**split_result;
	
	t_env	local_env;
	t_echo	bis;
}			t_general;

typedef struct s_signals
{
	int		i;
}			t_signals;

///////////////////// ECHO ////////////////////////
void		init_eko(t_echo *eko, t_general *g);
int			echo_take_of_simple_quote(char *str, t_echo *eko, int n,
				t_general *g);
char		*remake_str(char **tab, t_echo *eko, int i);
void		prepare_echo(char **tab, t_echo *eko, char **str, char **tmp);
void		execute_echo(char **tab, t_echo *eko, char *str, char *tmp);
void		finalize_echo(char **tab, t_echo *eko, char *tmp, char *str);
void		echo(char **tab, t_echo *eko, t_general *g);
int			handle_consecutive_quotes(char *str, t_echo *eko);
int			handle_single_double_quote(char *str, t_echo *eko, int *flag);
void		copy_non_special_char(char *str, t_echo *eko, t_general *g);
void		echo_args(char *str, t_echo *eko, char *tmp, t_general *g);
int			handle_double_quote(char *str, t_echo *eko, int *i, int *test);
int			handle_single_quote(char *str, t_echo *eko, int *i, int *test);
char		*echo_verif_quote(char *str, t_echo *eko, t_general *g);
char		*handle_remaining_chars(char *str, t_echo *eko, int test);
int			process_single_quotes(char *str, t_echo *eko, int *i, int *test);
int			process_double_quotes(char *str, t_echo *eko, int *i, int *test);
void		echo_verif_3(t_echo *eko, t_general *g);
void		echo_verif_3_n(t_echo *eko, t_general *g);
char		*remake_str_bis(char **tab);
int			dollar_bis(char *str, t_echo *eko, t_general *g);
void	copy_normal_char_bis(char *str, t_echo *eko, int *i, t_general *g);
int	handle_variable_expansion(char *str, t_echo *eko, int *i, t_general *g);
char	*extract_env_variable_name(char *str, int *i);


///////////////////// ENV ///////////////////////////
void		ft_export(t_general *g, char **args, t_echo *eko);
void		ft_env(t_env *env, t_general *g);
void		ft_unset(t_env *env, char **args, t_general *g);
unsigned int	hash_function(const char *key, unsigned int table_size);
char	*get_key(char *env_var);
char	*get_value(char *env_var);
t_var	*create_var(char *key, char *value, bool env_flag);
void	delete_var(t_var *var);
char	**get_local_env(t_env *env);
char	*tvar_to_str(t_var *var);
void	init_local_env(t_env *local_env, char **envp);
void	dup_env(t_env *local_env, char **envp);
void	rest_value(t_var *var, char *new_value);
void	ft_add_var(t_env *env, char *env_str, bool flag);
t_list	*exist_env_var(char *key, t_list *lst);
void	delete_env(t_env *env);
int	cond(void *key, void *content);
void	del(void *content);


///////////////////// REDIRECTION ///////////////////////////
void		skip_white_space(char *str, int i, char *output);
int			handle_redirections_and_execute(char *cmd, t_general *g);
int			handle_single_redirection(char *filename, char *redir_type,
				t_general *g);
void	restore_standard_fds(int saved_stdout, int saved_stdin, t_general *g);
int	handle_single_redirection(char *filename, char *redir_type, t_general *g);
int	apply_redirection(int fd, char *redir_type, t_general *g);

///////////////////// PARSING ///////////////////////////
int			check_special_characters(const char *str);
void		count_commands(char *command_line, t_general *g);
int			count_redirections(char *str);
int			is_redirection(char c);
char		*ft_strncpy(char *dest, const char *src, size_t n);
int			verif_quote_2(char *str, int i, int *double_quote_count,
				int *single_quote_count);
char		*verif_quote(char *str);
void		check_redirection_2(int *expecting_command, int *i, char *str);
int			is_space(char *str, int *i);
int			check_redirections(char *str);
char		**split_delimiters(const char *str, int *result_size);
char		**split_file(char *str, int *result_size);
char		**cmd_args(char *line);
char		*ft_get_prompt(void);
char		*trim_space(char *str);
char		**split_delimiters(const char *str, int *result_size);
int	is_space_bis(char *str);
int	is_space(char *str, int *i);
void	check_redirection_2(int *expecting_command, int *i, char *str);
int	verif_quote_2(char *str, int i, int *double_quote_count,
		int *single_quote_count);


///////////////////// BUILTINS ///////////////////////////
void		ft_exit(char **tab, t_general *g, t_echo *eko);



///////////////////// PIPE ///////////////////////////
char		**split_by_pipe(char *cmd);
void		execute_pipeline(char **commands, t_general *g);
int			count_pipe(char *str);
void		echo_bis(char **tab, t_echo *eko, t_general *g);
int			handle_redirections_and_execute_bis(char *cmd, t_general *g);







int			is_delimiter(char c);
char		**split_str(char *str, int *num_tokens, t_general *g);
void		count_commands(char *command_line, t_general *g);
int			check_special_characters(const char *str);
char		*based_path(char *cmd, t_general *g);
char		*verif_quote(char *str);
void		main_signal(void);
void		sig_handler(int sig);
void		pipe_while(t_general *g);
void		ft_execve(char *line, char *tab_cmd, t_general *g);
int			builtin(char *line, t_env *local_env, t_general *g);
void		cd_project(char **tab, t_general *g);
void		pwd(char **tab, t_general *g);
void		export(char **tab);
int			dollar_double(char *str, t_echo *eko);
int			echo_take_of_double_quote(char *str, t_echo *eko, int n,
				t_general *g);
int			dollar(char *str, t_echo *eko, t_general *g);
int			dollar_n(char *str, t_echo *eko, t_general *g);
int			direction_double_n(char *str, t_echo *eko, t_general *g,
				char *line);
int			is_space_bis(char *str);
char		*verif_quote_bis(char *str);
int			handle_error_1(int save_stdin, int save_stdout, t_general *g);
int			handle_error_2(t_general *g, char *cmd);
void		handle_error_3(t_general *g, int *fd, int *i);
int			count_delimiters(const char *str);
void		toggle_quotes(char c, int *in_single_quotes, int *in_double_quotes);
char		**split_by_pipe(char *cmd);
int			synthax(t_general *g);
int			brut(t_general *g);
void		full_free(t_general *g);
void		boucle(t_general *g);
void		init_tab(t_general *g);
char 		*vide_quote(char **tab);


#endif