# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tissad <issad.tahar@icloud.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 12:06:21 by tissad            #+#    #+#              #
#    Updated: 2024/04/04 17:45:32 by tissad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Options de compilation
CC=gcc
CFLAGS=-Wall -Wextra -Werror
AR=ar
ARFLAGS=-rcs
#Commandes shell
RMF=rm -f
#fichiers source obligatoire
SOURCES=./src/ft_atoi.c\
		./src/ft_bzero.c\
		./src/ft_calloc.c\
		./src/ft_isalnum.c\
		./src/ft_isalpha.c\
		./src/ft_isascii.c\
		./src/ft_isdigit.c\
		./src/ft_isprint.c\
		./src/ft_itoa.c\
		./src/ft_memchr.c\
		./src/ft_memcmp.c\
		./src/ft_memcpy.c\
		./src/ft_memmove.c\
		./src/ft_memset.c\
		./src/ft_putchar_fd.c\
		./src/ft_putendl_fd.c\
		./src/ft_putnbr_fd.c\
		./src/ft_putstr_fd.c\
		./src/ft_split.c\
		./src/ft_strchr.c\
		./src/ft_strdup.c\
		./src/ft_striteri.c\
		./src/ft_strjoin.c\
		./src/ft_strlcat.c\
		./src/ft_strlcpy.c\
		./src/ft_strlen.c\
		./src/ft_strmapi.c\
		./src/ft_strcmp.c\
		./src/ft_strncmp.c\
		./src/ft_strnstr.c\
		./src/ft_strrchr.c\
		./src/ft_strtrim.c\
		./src/ft_substr.c\
		./src/ft_tolower.c\
		./src/ft_toupper.c\
		./src/get_next_line.c\
		./src/ft_strtol.c\
		./src/ft_strspn.c\
		./src/ft_strcspn.c\
		./src/ft_strtok.c\
		./src/ft_strcpy.c\
		./src/ft_strcat.c\
		./src/ft_strtod.c\
		./ft_printf_src/ft_printf.c\
		./ft_printf_src/ft_printf_just.c\
		./ft_printf_src/ft_printf_itoa_base.c\
		./ft_printf_src/ft_printf_get_flags.c\
		./ft_printf_src/ft_printf_convert.c\
		./ft_printf_src/ft_printf_convert_i.c
#Fichiers source bonus
S_BONUS = ft_lstnew.c\
ft_lstadd_front.c\
ft_lstsize.c\
ft_lstlast.c\
ft_lstadd_back.c\
ft_lstdelone.c\
ft_lstclear.c\
ft_lstiter.c\
ft_lstmap.c
#Variable Make
OBJECTS=$(SOURCES:.c=.o)
O_BONUS=$(S_BONUS:.c=.o)
INCLUDES=-I ./includes
EXEC=libft.a
#La regle all
all: $(EXEC)
#Compilation de la libft
$(EXEC): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

#Compilation des objets
%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(EXEC) $(O_BONUS)
	$(AR) $(ARFLAGS) $^
%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#La regle clean supprime les .o objets
clean:
	$(RMF) *.o $(OBJECTS) $(O_BONUS)
#La regle fclean supprime les .o et l'executable
fclean: clean
	$(RMF) $(EXEC)
#La regle re qui suprime les .o et l'executable puis compile
re: fclean all

.PHONY: all clean fclean re
