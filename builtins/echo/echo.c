/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/15 16:50:55 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include "../env.h"

#define PATH_MAX 4096

int direction_double(char *str, int i, t_echo *eko)
{
        char output[1024];
    int j = 0;
    int fd;
    int saved_stdout;

    ++i;
    ++i;
    while (str[i] && str[i] <= 32) {
        ++i;
    }
    while (str[i] && j < 1023) {
        output[j++] = str[i++];
    }
    output[j] = '\0';
    fd = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Sauvegarder STDOUT_FILENO pour restaurer plus tard
    saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout < 0) {
        perror("dup");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Rediriger la sortie standard vers le fichier en mode append
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    // Afficher le contenu de l'echo dans le fichier
    printf("%s\n", eko->line);

    // Restaurer STDOUT_FILENO
    if (dup2(saved_stdout, STDOUT_FILENO) < 0) {
        perror("dup2");
        close(saved_stdout);
        exit(EXIT_FAILURE);
    }
    close(saved_stdout);

    return 0;
}

int direction(char *str, int i, t_echo *eko) 
{
    char output[1024];
    int j = 0;
    int fd;
    int saved_stdout;

    ++i;
    while (str[i] && str[i] <= 32) {
        ++i;
    }
    while (str[i] && j < 1023) {
        output[j++] = str[i++];
    }
    output[j] = '\0';

    fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout < 0) {
        perror("dup");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    printf("%s\n", eko->line);

    if (dup2(saved_stdout, STDOUT_FILENO) < 0) {
        perror("dup2");
        close(saved_stdout);
        exit(EXIT_FAILURE);
    }
    close(saved_stdout);

    return 0;
}

char *echo_verif_quote(char *str, t_echo *eko)
{
        int i;
        int flag;
        int flag_i;
        int test;

        i = 0;
        eko->line[0] = '\0';
        while (str[i])
        {
                flag_i = 0;
                flag = 0;
                if ((str[i] == '"'))
                {
                        while (str[i])
                        {
                                ++i;
                                if (str[i] == '"')
                                        {
                                                if (echo_take_of_double_quote(str, eko, i) == -1)
                                                        return (NULL);
                                                ++i;
                                                flag_i = 1;
                                                test = i;
												flag = 1;
										}
                                if (flag == 1)
                                        break;
                        }
						if (flag == 1)
                                continue;
                        return (printf("minishell: %s: command not found\n", str), NULL);      
                        
                     
                }
                flag = 0;
                if (str[i] == 39)
                {
                        while (str[i])
                        {
                                ++i;
                                if (str[i] == 39)
                                        {
                                                flag = 1;
                                                echo_take_of_simple_quote(str, eko, i);
                                                ++i;
                                                test = i;
                                        }
                                if (flag == 1)
                                        break;
                        }
                        if (flag == 1)
                                continue;
                      	return (printf("minishell: %s: command not found\n", str), NULL);
                }
                if (flag_i == 0)
                        ++i;
        }
        if (eko->line[0] == '\0')
                return (eko->line);
        if (test != i)
        {
                while (str[test] && (str[test] != '<' && str[test] != '>'))
                {

                        eko->line[eko->j] = str[test];
                        eko->j++;
                        test++;
                }
                eko->line[eko->j] = '\0';
        }
        if ((str[test] == '>' && str[test + 1] == '>')
                || (str[test] == '<' && str[test + 1] == '<'))
        {
                direction_double(str, test, eko);
                return (NULL);
        }
        if (str[test] == '>' || str[test] == '<')
        {
                direction(str, test, eko);
                return (NULL);
        }
        return (eko->line);
}

void echo_args(char *str, t_echo *eko, char **tab, char *tmp)
{
        if (tmp[0] == '\0')
        {
                dollar_n(str, eko);
                free_tab(tab);
                return;
        }
        printf("%s", tmp);
        free_tab(tab);
}
char *remake_str(char **tab, t_echo *eko, int i)
{
        int j;
        int k;
        char *new_str;
        
        if (tab[i] == NULL)
                return (NULL);
        new_str = malloc(sizeof(char) * eko->len_str + 1);
        if (new_str == NULL)
                return (NULL);
        j = 0;
        k = 0;
        
                
        while (tab[i])
        {
                while(tab[i][j])
                {
                        new_str[k] = tab[i][j];
                        ++k;
                        ++j;
                }
                if (tab[i + 1] != NULL)
                        new_str[k] = ' ';
                ++k;
                j = 0;
                ++i;
        }
        k--;
        new_str[k] = '\0';
        return(new_str);
}

void echo(char **tab, t_echo *eko)
{
    char *str = NULL;
    char *tmp = NULL;

    if (tab[1] && ft_strcmp(tab[1], "-n") == 0)
                str = remake_str(tab, eko, 2);
        else (str = remake_str(tab, eko, 1));

    if (!str) 
    {
        free_tab(tab);
        free(str);
        return;
    }
    eko->line = malloc(sizeof(char) * (eko->len_str + PATH_MAX + 1));
    if (!eko->line) 
    {    
        free(str); 
        return;
    }
    tmp = echo_verif_quote(str, eko);
    if (tmp == NULL)
    {
        free(eko->line);
        free(str); 
        return;
    }

    if (tab[1] && ft_strcmp(tab[1], "-n") == 0) 
    {
        echo_args(str, eko, tab, tmp);
        free(eko->line);
        free(str);
        return;
    }

    if (*tmp == '\0') 
    {
        dollar(str, eko);
        free_tab(tab);
        free(eko->line);
        free(str);
        return;
    }
    
    printf("%s\n", tmp);
    free_tab(tab);
    free(eko->line);
    free(str);
}

void init_eko(t_echo *eko, char *line)
{
        (void)line;
        eko->len_str = 200;
        eko->i = 0;
        eko->j = 0;
        eko->flag_double = 0;
        eko->flag_simple = 0;
        eko->line = NULL;
        eko->flag_print = 0;
        eko->$ = 0;
}

void missingknow(t_echo *eko)
{
        printf("%d\n", eko->$);
}

int check_line(char *line)
{
        int i;

        i = 0;
        if (*line == '\0')
	        return (1);
        while (line[i])
        {
                if(is_delimiter(line[i]))
                        return (1);
                ++i;
        }
        return (0);
}
int builtin(char *line, t_env *local_env)
{
        
        char **tab;
        t_echo eko;
        
        if (check_line(line))
                return (0);
        init_eko(&eko, line);
        tab = ft_split(line, ' ');
        if (ft_strcmp(tab[0], "echo") != 0 
                && ft_strcmp(tab[0], "cd") != 0
                && ft_strcmp(tab[0], "pwd") != 0
                && ft_strcmp(tab[0], "env") != 0
                && ft_strcmp(tab[0], "exit") != 0
                && tab[1] == NULL)
                return (0);
        if (tab[1] == NULL)
                return (1);
        if (ft_strcmp(tab[0], "echo") == 0
                && ft_strcmp(tab[1], "$?") == 0)
            return (missingknow(&eko), 1);    
        if (ft_strcmp(tab[0], "echo") == 0)
            return (echo(tab, &eko), 1);
        if (ft_strcmp(tab[0], "cd") == 0)
             return (cd_project(tab, local_env), 1);
        if (ft_strcmp(tab[0], "pwd") == 0)
            return (pwd(tab), 1);
        if (ft_strcmp(tab[0], "env") == 0)
            return (ft_env(local_env), 1);
        if (ft_strcmp(tab[0], "exit") == 0)
            return (exit(1), 1);
	free_tab(tab);
        return(0);
}
