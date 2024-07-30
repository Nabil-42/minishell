/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:37:06 by nabil             #+#    #+#             */
/*   Updated: 2024/07/30 10:54:37 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include <errno.h>
#include <libft.h>
#include <signal.h>

volatile sig_atomic_t	g_flag = 0;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_flag == 1)
		{
			g_flag = 0;
			printf("\n");
		}
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}

}

void	main_signal(void)
{
struct sigaction sa;

    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction SIGINT");
        exit(EXIT_FAILURE);
    }

    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
    {
        perror("sigaction SIGQUIT");
        exit(EXIT_FAILURE);
    }
}
