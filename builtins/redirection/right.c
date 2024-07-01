/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:14:54 by nabil             #+#    #+#             */
/*   Updated: 2024/07/01 20:04:06 by nabil            ###   ########.fr       */
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
		g->$ = 500;
		perror("dup2");
	}
	close(saved_stdout);
	close(saved_stdin);
}

int	handle_single_redirection(char *filename, char *redir_type, t_general *g)
{
	int	fd;

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
		g->$ = 602;
		return (-1);
	}
	if (fd < 0)
	{
		perror(filename);
		g->$ = 601;
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
			perror("dup2");
			close(fd);
			g->$ = 998;
			return (-1);
		}
	}
	else if (strcmp(redir_type, "<") == 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(fd);
			g->$ = 997;
			return (-1);
		}
	}
	else
	{
		fprintf(stderr, "Unknown redirection type: %s\n", redir_type);
		g->$ = 999;
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
			return (printf("%d\n", g->$), (void)0);
		else if(g->flag_eko_n == 3)
			return;
		else if (g->flag_eko_n == 4)
		{
			printf("%s\n", g->path);
			free(g->path);
		}
		else if (g->flag_eko_n == 6)
			printf("\n");
		if (g->handle_eko != NULL)
		     free(g->handle_eko);
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
	// char	*str;
	t_echo	ikou;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	i = 0;
	if (saved_stdout < 0 || saved_stdin < 0)
	{
		perror("dup");
		g->$ = 1;
		return (-1);
	}
	g->tab_cmd = split_str(cmd, &g->nbr_dir);
	if (ft_strcmp(g->tab_cmd[0], "''") == 0 || ft_strcmp(g->tab_cmd[0], "\"\"") == 0)
	{
		return (printf("minishell: %s: command not found\n", cmd), 
		g->$ = 42, -1);
	}
	
	echo_bis(g->tab_cmd, &ikou, g);
	// printf("nabil = %s\n", ikou.line);
	    printf("tab_cmd[0] = %s\n", g->tab_cmd[0]);
	//     printf("tab_cmd[2] = %s\n", g->tab_cmd[2]);
	g->tab_dir = split_delimiters(cmd, &g->nbr_dir);
	//     printf("tab_dir[%d] = %s\n",i, g->tab_dir[0]);
	//         printf("tab_dir[%d] = %s\n",i, g->tab_dir[1]);
	//         printf("tab_dir[%d] = %s\n",i, g->tab_dir[2]);
	g->tab_file = split_file(cmd, &g->nbr_file);
	// printf("tab_dir[%d] = %s\n",i, g->tab_file[0]);
	// printf("tab_dir[%d] = %s\n",i, g->tab_file[1]);
	// printf("tab_dir[%d] = %s\n",i, g->tab_file[2]);
	// str = remake_str_bis(g->tab_cmd);
	// printf("NABIL = %s\n", str);
	while (i < g->nbr_file)
	{
		fd = handle_single_redirection(g->tab_file[i], g->tab_dir[i], g);
		if (fd < 0)
		{
			restore_standard_fds(saved_stdout, saved_stdin, g);
			g->$ = 1;
			return (-1);
		}
		if (apply_redirection(fd, g->tab_dir[i], g) < 0)
		{
			restore_standard_fds(saved_stdout, saved_stdin, g);
			g->$ = 1;
			return (-1);
		}
		i++;
	}
	exe_cmd(ikou.line, g);
	restore_standard_fds(saved_stdout, saved_stdin, g);
	free_tab(g->tab_dir);
	free_tab(g->tab_cmd);
	free_tab(g->tab_file);
	return (2);
}

