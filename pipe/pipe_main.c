/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:12:17 by nabil             #+#    #+#             */
/*   Updated: 2024/07/01 18:48:21 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"
#include <errno.h>
#include <libft.h>
#include <readline/history.h>
#include <readline/readline.h>

extern volatile sig_atomic_t	flag;

void execute_pipeline(char **tab_pipe, t_general *g) 
{
    int pipe_fds[2];
    int input_fd = 0; // Input file descriptor for the first command
    pid_t pid;
    int i = 0;
    flag = 1;

    while (tab_pipe[i] != NULL) {
        if (tab_pipe[i + 1] != NULL) {
            if (pipe(pipe_fds) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        // Fork a new process
        if ((pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Child process
            if (i > 0) { // If not the first command, get input from the previous pipe
                if (dup2(input_fd, 0) == -1) {
                    perror("dup2 input_fd");
                    exit(EXIT_FAILURE);
                }
                close(input_fd);
            }

            if (tab_pipe[i + 1] != NULL) { // If not the last command, output to the current pipe
                if (dup2(pipe_fds[1], 1) == -1) {
                    perror("dup2 pipe_fds[1]");
                    exit(EXIT_FAILURE);
                }
                close(pipe_fds[1]);
                close(pipe_fds[0]);
            }

            // Execute the current command
            handle_redirections_and_execute(tab_pipe[i],g);
        } else { // Parent process
            wait(NULL); // Wait for the child process to complete
            if (input_fd != 0) {
                close(input_fd);
            }
            if (tab_pipe[i + 1] != NULL) {
                close(pipe_fds[1]);
                input_fd = pipe_fds[0]; // Save the input for the next command
            }
        }
        i++;
    }
}

void	pipe_while(t_general *g)
{
	int		pipefd[2];
	pid_t	pid;
	int		i;
	int		k;

	int num_pipes = g->count;
        flag = 1;

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
            free_tab(g->tab_cmd);
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