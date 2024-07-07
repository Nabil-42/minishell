/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:14:54 by nabil             #+#    #+#             */
/*   Updated: 2024/07/07 12:07:33 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "../env/env.h"

void	skip_white_space(char *str, int i, char *output)
{
	int	j;

	j = 0;
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

char	*skip(char *str)
{
	char	*buff;
	int		i;
	int		k;

	k = 0;
	i = 0;
	buff = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (buff == NULL)
		return (NULL);
	while (str[i] && (str[i] <= 32 || str[i] == '.' || str[i] == '/'))
	{
		i++;
	}
	while (str[i] && str[i] != 32)
	{
		buff[k] = str[i];
		++i;
		++k;
	}
	buff[k] = '\0';
	return (buff);
}

void	restore_standard_fds(int saved_stdout, int saved_stdin, t_general *g)
{
	if (dup2(saved_stdout, STDOUT_FILENO) < 0 || dup2(saved_stdin,
			STDIN_FILENO) < 0)
	{
		g->exval = 1;
		// perror("dup2");
	}
	close(saved_stdout);
	close(saved_stdin);
}

int	handle_single_redirection(char *filename, char *redir_type, t_general *g)
{
	int	fd;

	// printf("handle line = %s\n ", filename);
	if (strcmp(redir_type, ">") == 0)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (strcmp(redir_type, ">>") == 0)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (strcmp(redir_type, "<") == 0)
	{
		fd = open(filename, O_RDONLY);
	}
	else
	{
		fprintf(stderr, "Unknown redirection type: %s\n", redir_type);
		g->exval = 602;
		return (-1);
	}
	if (fd < 0)
	{
		g->exval = 1;
		ft_fprintf(2, "%s: 2 No such file or directory\n", filename);
		return (-1);
	}
	return (fd);
}

int	apply_redirection(int fd, char *redir_type, t_general *g)
{
	if (strcmp(redir_type, ">") == 0 || strcmp(redir_type, ">>") == 0)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			// perror("dup2");
			close(fd);
			g->exval = 998;
			return (-1);
		}
	}
	else if (strcmp(redir_type, "<") == 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			// perror("dup2");
			close(fd);
			g->exval = 997;
			return (-1);
		}
	}
	else
	{
		fprintf(stderr, "Unknown redirection type: %s\n", redir_type);
		g->exval = 999;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

void	exe_cmd(char *cmd, t_general *g)
{
	if (builtin(cmd, &g->local_env, g))
	{
		
		if (g->flag_eko_n == 0 && g->handle_eko[0] != ' ')
			printf("%s\n", g->handle_eko);
		else if (g->flag_eko_n == 1)
			printf("%s", g->handle_eko);
		else if(g->flag_eko_n == 2)
			return (printf("%d\n", g->exval), (void)0);
		else if(g->flag_eko_n == 3)
			return;
		else if (g->flag_eko_n == 4)
		{
			printf("%s\n", g->path);
			free(g->path);
		}
		else if (g->flag_eko_n == 6)
			return (printf("\n"), (void)0);
		if (g->handle_eko != NULL)
		{
		   	free(g->handle_eko);
			g->handle_eko = NULL;
		}
	}
	else if (g->nbr_pipe > 0)
		return (ft_execve(cmd, cmd, g));
	else
		(pipe_while(g));

	
}

int	handle_redirections_and_execute(char *cmd, t_general *g)
{
	int		fd;
	int		saved_stdout;
	int		saved_stdin;
	int		i;
	t_echo	ikou;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	i = 0;
	if (handle_error_1(saved_stdin, saved_stdout, g) == -1)
		return 1;
	g->nbr_dir = 0;
	g->tab_cmd = split_str(cmd, &g->nbr_dir);
	if (handle_error_2(g, cmd) == -1)
		return 1;	
	// printf(" ikou = %s\n", ikou.line);
	//    printf("tab_cmd[0] = %s\n", g->tab_cmd[0]);
	//     printf("tab_cmd[1] = %s\n", g->tab_cmd[1]);
	//     printf("tab_cmd[2] = %s\n", g->tab_cmd[2]);
	g->tab_dir = split_delimiters(cmd, &g->nbr_dir);
	//     printf("tab_dir[%d] = %s\n",i, g->tab_dir[0]);
	//         printf("tab_dir[%d] = %s\n",i, g->tab_dir[1]);
	//         printf("tab_dir[%d] = %s\n",i, g->tab_dir[2]);
	g->tab_file = split_file(cmd, &g->nbr_file);
	// printf("tab_file[%d] = %s\n",0, g->tab_file[0]);
	// printf("tab_file[%d] = %s\n",1, g->tab_file[1]);
	// printf("tab_file[%d] = %s\n",2, g->tab_file[2]);
	// printf("nbr dir %d\n", g->nbr_dir);
	// printf("file = %d\n", g->nbr_file);
	while (i < g->nbr_file)
	{
		handle_error_3(g, &fd, &i);
		if (fd < 0)
		{
			restore_standard_fds(saved_stdout, saved_stdin, g);
			g->exval = 1;
			++i;
			return 1;
		}
		if (apply_redirection(fd, g->tab_dir[i], g) < 0)
		{
			restore_standard_fds(saved_stdout, saved_stdin, g);
			g->exval = 2;
		}
		i++;
	}
	echo_bis(g->tab_cmd, &ikou, g);
	if (ikou.line)
		g->handle_ikou = ikou.line;
	// printf("dollar = %d\n", g->exval);
	exe_cmd(ikou.line, g);
	restore_standard_fds(saved_stdout, saved_stdin, g);
	if (ikou.line != NULL) 
	{
        free(ikou.line);
	    ikou.line = NULL; 
   	}
	return (2);
}

