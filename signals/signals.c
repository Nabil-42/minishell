/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:37:06 by nabil             #+#    #+#             */
/*   Updated: 2024/08/08 11:13:05 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include <errno.h>
#include <libft.h>
#include <signal.h>

volatile sig_atomic_t	g_flag = 0;

void	sig_handler_bis(int sig)
{
	if (sig == SIGCHLD)
	{
		if (sig == SIGINT)
		{
			g_flag = 2;
			printf("\n");
		}
	}
	if (sig == SIGQUIT)
	{
		g_flag = 3;
		printf("\n");
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_flag == 1)
		{
			g_flag = 2;
			printf("\n");
		}
		else
		{
			g_flag = 2;
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	if (sig == SIGCHLD)
	{
		g_flag = 3;
		printf("\n");
	}
}

void	main_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction SIGINT");
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
}

void	main_signal_tris(void)
{
	g_flag = 2;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
}

void	main_signal_bis(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler_bis;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction SIGQUIT");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction SIGQUIT");
		exit(EXIT_FAILURE);
	}
}
