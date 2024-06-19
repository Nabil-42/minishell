/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:25:28 by nabil             #+#    #+#             */
/*   Updated: 2024/06/19 20:26:29 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

int handle_input_redirection(const char *filename) 
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }

    // Rediriger l'entrée standard (stdin) vers le fichier
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("Erreur lors de la redirection de l'entrée standard");
        close(fd);
        return -1;
    }

    // Fermer le descripteur de fichier dupliqué
    close(fd);

    return 0;
}