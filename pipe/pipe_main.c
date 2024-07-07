/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:12:17 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 15:26:59 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "../includes/minishell.h"
#include <errno.h>
#include <libft.h>
#include <readline/history.h>
#include <readline/readline.h>

extern volatile sig_atomic_t	g_flag;

void execute_pipeline(char **tab_pipe, t_general *g) 
{
    int pipe_fds[2];
    int input_fd = 0;
    pid_t pid;
    int i = 0;
	g_flag = 1;
	
    while (tab_pipe[i] != NULL) {
        if (tab_pipe[i + 1] != NULL) {
            if (pipe(pipe_fds) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        if ((pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { 
            if (i > 0) { 
                if (dup2(input_fd, 0) == -1) {
                    perror("dup2 input_fd");
                    exit(EXIT_FAILURE);
                }
                close(input_fd);
            }

            if (tab_pipe[i + 1] != NULL) { 
                if (dup2(pipe_fds[1], 1) == -1) {
                    perror("dup2 pipe_fds[1]");
                    exit(EXIT_FAILURE);
                }
                close(pipe_fds[1]);
                close(pipe_fds[0]);
            }

            handle_redirections_and_execute(tab_pipe[i], g);

            exit(EXIT_FAILURE);
        } else { 
            if (input_fd != 0) {
                close(input_fd);
            }
            if (tab_pipe[i + 1] != NULL) {
                close(pipe_fds[1]);
                input_fd = pipe_fds[0]; 
            } else {
                close(pipe_fds[0]);
            }
        }
        i++;
    }
    while (wait(NULL) > 0);
}


// void pipe_while(t_general *g)
// {
//     int		pipefd[2];
//     int     comm_pipe[2];
//     pid_t	pid;
//     int		i;
//     int		k;
//     int     num_pipes = g->count;
//     g_flag = 1;

//     if (pipe(comm_pipe) == -1) 
//     {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     i = 0;
//     k = 0;
//     int prev_pipe_read = -1;
//     while (i <= num_pipes)
//     {
//         if (i < num_pipes && pipe(pipefd) == -1)
//         {
//             perror("pipe");
//             exit(EXIT_FAILURE);
//         }
//         pid = fork();
//         if (pid == -1)
//         {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }
//         else if (pid == 0)
//         { 
//             if (prev_pipe_read != -1)
//             {
//                 dup2(prev_pipe_read, 0);
//                 close(prev_pipe_read);  
//             }
//             if (i < num_pipes)
//             {
//                 close(pipefd[0]);  
//                 dup2(pipefd[1], 1);
//                 close(pipefd[1]);  
//             }

//             close(comm_pipe[0]);  
//             ft_execve(g->tab_cmd[0], g->tab_cmd[0], g);
//             int return_value = g->exval; // Remplacez par votre propre valeur
//             write(comm_pipe[1], &return_value, sizeof(return_value));
//             exit(EXIT_FAILURE);
//         }
//         else
//         { 
//             if (prev_pipe_read != -1)
//             {
//                 close(prev_pipe_read);
//             }
//             if (i < num_pipes)
//             {
//                 close(pipefd[1]);          
//                 prev_pipe_read = pipefd[0];
//             }

//             waitpid(pid, &g->status, 0);

//             if (i == num_pipes)  
//             {
//                 close(comm_pipe[1]);  
//                 int received_value;
//                 read(comm_pipe[0], &received_value, 3);
//                 g->exval = (int)received_value;
//                 close(comm_pipe[0]);
//             }

//             i++;
//             k++;
//         }
//     }
//     if (prev_pipe_read != -1)
//     {
//         close(prev_pipe_read);
//     }
// }


