/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:12:17 by nabil             #+#    #+#             */
/*   Updated: 2024/06/20 18:03:30 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minishell.h"
#include <errno.h>
#include <libft.h>
#include <readline/history.h>
#include <readline/readline.h>

extern volatile sig_atomic_t	flag;

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
			ft_execve(g->line, g->tab_cmd[k]);
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
