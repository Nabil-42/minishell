/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:12:17 by nabil             #+#    #+#             */
/*   Updated: 2024/06/23 19:26:42 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"
#include <errno.h>
#include <libft.h>
#include <readline/history.h>
#include <readline/readline.h>

extern volatile sig_atomic_t	flag;

void execute_pipeline(char **commands, t_general *g, int *redir_counts, char ***redir_types) 
{
    int pipe_fd[2];
    pid_t pid;
    int i = 0;

    while (commands[i] != NULL) 
    {
        if (commands[i + 1] != NULL) 
	{
            if (pipe(pipe_fd) < 0) 
	    {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid = fork();
        if (pid < 0) 
	{
            perror("fork");
            exit(EXIT_FAILURE);
        } 
	else if (pid == 0)
	{
            if (commands[i + 1] != NULL) {
                if (dup2(pipe_fd[1], STDOUT_FILENO) < 0) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            handle_redirections_and_execute(commands[i], g, redir_counts[i], redir_types[i]);
            printf("teste COMBIEN ?\n");
            exit(EXIT_SUCCESS);
        }
	else {
            if (commands[i + 1] != NULL) {
                if (dup2(pipe_fd[0], STDIN_FILENO) < 0) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
            wait(NULL);
        }
        i++;
    }
}



char **split_by_pipe(char *cmd) 
{
    int i = 0;
    int count = 1;
    char **result;
    char *temp, *cmd_copy;

    while (cmd[i] != '\0') {
        if (cmd[i] == '|') {
            count++;
        }
        i++;
    }

    result = malloc((count + 1) * sizeof(char *));
    if (result == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    cmd_copy = ft_strdup(cmd);
    if (cmd_copy == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    temp = strtok(cmd_copy, "|");
    i = 0;
    while (temp != NULL) 
    {
        result[i] = ft_strdup(temp);
        if (result[i] == NULL) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        i++;
        temp = ft_strtok(NULL, "|");
    }
    result[i] = NULL;

    free(cmd_copy);

    return result;
}



void	pipe_while(t_general *g)
{
	int		pipefd[2];
	pid_t	pid;
	int		i;
	int		k;

	int num_pipes = g->count; // Nombre de pipes à créer (ici, 2 pipes)
	i = 0;
	k = 0;
	int prev_pipe_read = -1;
		// Descripteur de fichier pour la lecture du pipe précédent
	while (i <= num_pipes)
	{
		// Créer le pipe
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
		{ // Processus fils
			// Redirection de l'entrée standard si ce n'est pas le premier processus
			if (prev_pipe_read != -1)
			{
				dup2(prev_pipe_read, 0);
					// Rediriger l'entrée standard depuis le pipe précédent
				close(prev_pipe_read);  
					// Fermer le descripteur de fichier du pipe précédent
			}
			// Redirection de la sortie standard vers le pipe actuel sauf pour la dernière commande
			if (i < num_pipes)
			{
				close(pipefd[0]);  
					// Ferme l'extrémité de lecture du pipe dans le processus fils
				dup2(pipefd[1], 1);
					// Rediriger la sortie standard vers l'extrémité d'écriture du pipe
				close(pipefd[1]);  
					// Fermer l'extrémité d'écriture du pipe dans le processus fils
			}
			// Exécution de la commande avec execve
			ft_execve(g->line, g->tab_cmd[k], g);
			exit(EXIT_FAILURE);
		}
		else
		{ // Processus parent
			if (prev_pipe_read != -1)
			{
				close(prev_pipe_read);
					// Fermer le descripteur de fichier du pipe précédent
			}
			if (i < num_pipes)
			{
				close(pipefd[1]);          
					// Fermer l'extrémité d'écriture du pipe dans le processus parent
				prev_pipe_read = pipefd[0];
					// Mettre à jour prev_pipe_read pour lire à partir du pipe actuel dans la prochaine itération
			}
			// Attendre que le processus fils se termine
			waitpid(pid, &g->status, 0);
			// Incrémenter les compteurs pour la boucle while
			i++;
			k++;
		}
	}
	// Fermer le descripteur de fichier du dernier pipe après avoir terminé les itérations
	if (prev_pipe_read != -1)
	{
		close(prev_pipe_read);
	}
}
