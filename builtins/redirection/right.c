/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:14:54 by nabil             #+#    #+#             */
/*   Updated: 2024/06/26 11:13:56 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

void	skip_white_space(char *str, int i, char *output)
{
	int	j;

	j = 0;
	++i;
	while (str[i] && str[i] <= 32)
	{
		++i;
	}
	while (str[i] && j < 1023)
	{
		output[j++] = str[i++];
	}
	output[j] = '\0';
}


char	*skip(char *str)
{
	char *buff;
	int i;
	int k;
	k = 0;
	i = 0;

	buff = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (buff == NULL)
		return NULL;
	while (str[i] && (str[i] <= 32 || str[i] == '.' || str[i] == '/'))
	{
		i++;
	}
	while (str[i] && str[i] != 32)
	{
		
		buff[k] = str[i];
		++i;
		++k;
	}
	buff[k] = '\0';
	
	return(buff);
}

void restore_standard_fds(int saved_stdout, int saved_stdin, t_general *g) 
{
    if (dup2(saved_stdout, STDOUT_FILENO) < 0 || dup2(saved_stdin, STDIN_FILENO) < 0) 
    {
	g->$ = 500;
        perror("dup2");
    }
    close(saved_stdout);
    close(saved_stdin);
}

int handle_single_redirection(char *filename, char *redir_type, t_general *g) 
{
    int fd;

    if (strcmp(redir_type, ">") == 0) 
    {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	g->check_pipe = 2;
    } 
    else if (strcmp(redir_type, ">>") == 0) 
    {
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	g->check_pipe = 2;
    } 
    else if (strcmp(redir_type, "<") == 0) 
    {
        fd = open(filename, O_RDONLY);
	g->check_pipe = 2;
    } 
    else 
    {
        fprintf(stderr, "Unknown redirection type: %s\n", redir_type);
	g->$ = 602;
        return -1;
    }
    if (fd < 0) 
    {
        perror(filename);
	g->$ = 601;
        return -1;
    }
	free(filename);
    
    
    return fd;
}


int apply_redirection(int fd, char *redir_type, t_general *g) 
{
    if (strcmp(redir_type, ">") == 0 || strcmp(redir_type, ">>") == 0)
    {
        if (dup2(fd, STDOUT_FILENO) < 0) 
	{
            perror("dup2");
            close(fd);
	    g->$ = 998;
            return -1;
        }
    } 
    else if (strcmp(redir_type, "<") == 0) 
    {
        if (dup2(fd, STDIN_FILENO) < 0) 
	{
            perror("dup2");
            close(fd);
	    g->$ = 997;
            return -1;
        }
    } 
    else 
    {
        fprintf(stderr, "Unknown redirection type: %s\n", redir_type);
	g->$ = 999;
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

void exe_cmd(char *cmd, t_general *g) 
{
	
	if (builtin(cmd, &g->local_env, g))
		;
	else if (g->nbr_pipe > 0) 
		ft_execve(cmd, cmd, g);
	else (pipe_while(g));
}

int handle_redirections_and_execute(char *cmd, t_general *g) 
{
    int fd;
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);
    int i = 0;
    char *str;

    if (saved_stdout < 0 || saved_stdin < 0) 
    {
        perror("dup");
	g->$ = 1;
        return -1;
    }
    g->tab_cmd = split_str(cmd, &g->nbr_dir);
        // printf("tab_cmd[%d] = %s\n",i, g->tab_cmd[0]);
        //     printf("tab_cmd[%d] = %s\n",i, g->tab_cmd[1]);
        //     printf("tab_cmd[%d] = %s\n",i, g->tab_cmd[2]);
    g->tab_dir = split_delimiters(cmd, &g->nbr_dir);
//     printf("tab_dir[%d] = %s\n",i, g->tab_dir[0]);
//         printf("tab_dir[%d] = %s\n",i, g->tab_dir[1]);
//         printf("tab_dir[%d] = %s\n",i, g->tab_dir[2]);
	g->tab_file = split_file(cmd, &g->nbr_file);
	// printf("tab_dir[%d] = %s\n",i, g->tab_file[0]);
        // printf("tab_dir[%d] = %s\n",i, g->tab_file[1]);
        // printf("tab_dir[%d] = %s\n",i, g->tab_file[2]);
	str = remake_str_bis(g->tab_cmd);
    while (i < g->nbr_file) 
    {
        fd = handle_single_redirection(g->tab_file[i], g->tab_dir[i], g);
        if (fd < 0) 
	{
            restore_standard_fds(saved_stdout, saved_stdin, g);
	    g->$ = 1;
            return -1;
        }
        if (apply_redirection(fd, g->tab_dir[i], g) < 0) 
	{
            restore_standard_fds(saved_stdout, saved_stdin, g);
	    g->$ = 1;
            return -1;
        }
        i++;
    }

    exe_cmd(str, g);

    restore_standard_fds(saved_stdout, saved_stdin, g);

    return (2);
}



int	direction(char *str, t_echo *eko, t_general *g, char *line)
{
	char	output[1024];
	int		fd;
	int		saved_stdout;
	int		i;

	i = 0;
	(void)g;
	(void)eko;
	skip_white_space(str, i, output);
	
	fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
		(perror("dup"), close(fd), exit(EXIT_FAILURE));
	if (dup2(fd, STDOUT_FILENO) < 0)
		(perror("dup2"), close(fd), exit(EXIT_FAILURE));
	(close(fd), printf("%s\n", line));
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
		(perror("dup2"), close(saved_stdout), exit(EXIT_FAILURE));
	close(saved_stdout);
	return (0);
}

int direction_$(char *str, t_echo *eko, t_general *g, int $)
{
	char	output[1024];
	int		fd;
	int		saved_stdout;
	int		i;

	i = 0;
	(void)g;
	(void)eko;
	skip_white_space(str, i, output);
	fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		(perror("open"), exit(EXIT_FAILURE));
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
		(perror("dup"), close(fd), exit(EXIT_FAILURE));
	if (dup2(fd, STDOUT_FILENO) < 0)
		(perror("dup2"), close(fd), exit(EXIT_FAILURE));
	(close(fd), printf("%d\n", $));
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
		(perror("dup2"), close(saved_stdout), exit(EXIT_FAILURE));
	close(saved_stdout);
	return (0);
}