/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:12:17 by nabil             #+#    #+#             */
/*   Updated: 2024/06/03 21:56:21 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <libft.h>
#include "../lib/libft/includes/libft.h"
#include <readline/history.h>
#include <readline/readline.h>

extern volatile sig_atomic_t flag;

void pipe_while(t_general *g)
{
       	int pipefd[2];
	int receiv_num;
        pid_t pid;
        
        if (pipe(pipefd) == -1) 
	{
            	perror("pipe");
        	exit(EXIT_FAILURE);
        }
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		receiv_num = 1;
		write(pipefd[1], &receiv_num, sizeof(receiv_num));
		close(pipefd[1]);
		ft_execve(g->line);
	}
	else 
	{
		close(pipefd[1]);
		read(pipefd[0], &receiv_num, sizeof(receiv_num));
		close(pipefd[0]);
		flag = receiv_num;
		waitpid(pid, &g->status, 0);
	}
}