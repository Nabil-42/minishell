/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:37:06 by nabil             #+#    #+#             */
/*   Updated: 2024/06/03 11:48:35 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>
#include <libft.h>
#include "../lib/libft/includes/libft.h"
#include <signal.h>

volatile sig_atomic_t flag = 0;

void sig_handler(int sig)
{
        if (sig == SIGINT)
        {       
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        printf("flag signal avant = %d\n", flag);
        flag = 1;
        printf("flag signal apres = %d\n", flag);
        }
}

void main_signal()
{
        struct sigaction sa;
        
        sa.sa_handler = &sig_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        if ((sigaction(SIGINT, &sa, NULL) == -1)
                || (sigaction(SIGQUIT, &sa, NULL) == -1))
        {
                perror("sigaction\n");
                exit(EXIT_FAILURE);
        }
}

