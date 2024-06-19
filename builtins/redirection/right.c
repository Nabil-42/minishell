/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:14:54 by nabil             #+#    #+#             */
/*   Updated: 2024/06/19 20:09:21 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

void skip_white_space(char *str, int i, char *output)
{
    int j = 0;
    
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

int direction(char *str, int dir, t_echo *eko) 
{
    char output[1024];
    int fd;
    int saved_stdout;
    int i;

    i = dir;
    skip_white_space(str, i, output);
    fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd < 0)
        (perror("open"),exit(EXIT_FAILURE));
    
    saved_stdout = dup(STDOUT_FILENO);
    
    if (saved_stdout < 0)
        (perror("dup"), close(fd), exit(EXIT_FAILURE));
    
    if (dup2(fd, STDOUT_FILENO) < 0)
        (perror("dup2"), close(fd), exit(EXIT_FAILURE));
    
    (close(fd), printf("%s\n", eko->line));
    
    if (dup2(saved_stdout, STDOUT_FILENO) < 0)
        (perror("dup2"), close(saved_stdout), exit(EXIT_FAILURE));
    
    close(saved_stdout);
    return 0;
}
