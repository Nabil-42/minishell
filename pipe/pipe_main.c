/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:12:17 by nabil             #+#    #+#             */
/*   Updated: 2024/06/27 12:44:29 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"
#include <errno.h>
#include <libft.h>
#include <readline/history.h>
#include <readline/readline.h>


void execute_pipeline(char **tab_pipe, t_general *g) 
{
    int pipe_fd[2];
    pid_t pid;
    int i = 0;
    int in_fd = STDIN_FILENO;

    while (tab_pipe[i] != NULL) {
        if (tab_pipe[i + 1] != NULL) {
            if (pipe(pipe_fd) < 0) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }
        
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (in_fd != STDIN_FILENO) {
                if (dup2(in_fd, STDIN_FILENO) < 0) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(in_fd);
            }
            if (tab_pipe[i + 1] != NULL) {
                if (dup2(pipe_fd[1], STDOUT_FILENO) < 0) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            printf("COMBIEN\n");
            g->check_pipe = 1;
            handle_redirections_and_execute(tab_pipe[i], g);
            
            exit(EXIT_FAILURE);
        } else {
            if (in_fd != STDIN_FILENO) {
                close(in_fd);
            }
            if (tab_pipe[i + 1] != NULL) {
                close(pipe_fd[1]);
                in_fd = pipe_fd[0];
            }
            wait(NULL);
        }
        i++;
    }

    if (in_fd != STDIN_FILENO) {
        close(in_fd);
    }
}

void	pipe_while(t_general *g, char *str)
{
	int		pipefd[2];
	pid_t	pid;
	int		i;
	int		k;

	int num_pipes = g->count; 
	i = 0;
	k = 0;
	int prev_pipe_read = -1;
	while (i <= num_pipes)
	{
		if (i < num_pipes && pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{ 
			if (prev_pipe_read != -1)
			{
				dup2(prev_pipe_read, 0);
				close(prev_pipe_read);  
			}
			if (i < num_pipes)
			{
				close(pipefd[0]);  
					
				dup2(pipefd[1], 1);
			
				close(pipefd[1]);  
					
			}
			
			
			ft_execve(g->tab_cmd[0], g->tab_cmd[0], g);
            free_tab(g->tab_pipe);free_tab(g->tab_dir);
	    	free_tab(g->tab_cmd);
	    	free(str);
	    	free_tab(g->tab_file);
			exit(EXIT_FAILURE);
		}
		else
		{ 
			if (prev_pipe_read != -1)
			{
				close(prev_pipe_read);
			}
			if (i < num_pipes)
			{
				close(pipefd[1]);          
				prev_pipe_read = pipefd[0];
			}
			waitpid(pid, &g->status, 0);
			i++;
			k++;
		}
	}
	if (prev_pipe_read != -1)
	{
		close(prev_pipe_read);
	}
}

char **split_by_pipe(char *cmd) 
{
    int i = 0;
    int count = 1;
    char **result;
    char *cmd_copy;
    char *token;

    while (cmd[i] != '\0') 
    {
        if (cmd[i] == '|') 
        {
            count++;
        }
        i++;
    }

    result = malloc((count + 1) * sizeof(char *));
    if (result == NULL) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    cmd_copy = ft_strdup(cmd);
    if (cmd_copy == NULL) 
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    i = 0;
    token = strtok(cmd_copy, "|");
    while (token != NULL) 
    {
        while (*token == ' ') token++;
        char *end = token + strlen(token) - 1;
        while (end > token && *end == ' ') end--;
        end[1] = '\0';

        result[i] = ft_strdup(token);
        if (result[i] == NULL) 
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        i++;
        token = strtok(NULL, "|");
    }
    result[i] = NULL;

    free(cmd_copy);

    return result;
}