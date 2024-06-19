/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:27:58 by tissad            #+#    #+#             */
/*   Updated: 2024/06/19 15:58:28 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>

/******************************************************************************/
/*                             Mandatory                                      */
/******************************************************************************/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strspn(const char *str, const char *delimiters);
int		ft_strcspn(const char *str, const char *delimiters);
int		ft_strtoi(const char *s, char **endptr);
char	*ft_strtok(char *str, const char *delimiters);
char	*ft_itoa(int n);
char	*ft_strdup(const char *src);
char	*ft_strndup(char const *src, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_bzero(void *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t	ft_strlen(char const *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strcmp(char const *s1, char const *s2);
double	ft_strtod(const char *str, char **endptr);
void	free_tab(char **tab);
int	ft_atoi_bis(const char *str);
/******************************************************************************/
/*                                  Bonus                                     */
/******************************************************************************/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
/*----------------------------------------------------------------------------*/
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstdelcond(t_list **lst, void *value, int (*cond)(void*, void*), \
void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/******************************************************************************/
/*                             get_next_line                                  */
/******************************************************************************/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define BUFFER_MAX 1

typedef struct s_buf
{
	char	*buf;
	size_t	size;
	size_t	max;
}	t_buf;
/*----------------------------------------------------------------------------*/
char	*get_next_line(int fd);
/******************************************************************************/
/*                               ft_printf                                    */
/******************************************************************************/
int		ft_printf(const char *str, ...);
int		ft_fprintf(int fd, const char *str, ...);

#endif
