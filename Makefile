# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabil <nabil@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/02 17:56:57 by tissad            #+#    #+#              #
#    Updated: 2024/06/19 21:11:11 by nabil            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#comipilation && shell cmd
CC			:= gcc -O0 -g
CFLAGS		:= -Wall -Wextra -Werror
RMF			:= rm -f
MK			:= mkdir
NR			:= norminette
NRCFLAGS	:= -R CheckForbiddenSourceHeader
NRHFLAGS	:= -R CheckDefine
GCL			:= git clone
GADD		:= git add
GCMT		:= git commit -m "auto commit: update"
GPUSH		:= git push
GREEN		:= \033[0;32m
NC			:= \033[0m
INFOS		:= infos
LIBFTDIR	:= ./lib/libft
LIBFT		:= $(LIBFTDIR)/libft.a
HDRS		:= ./includes
SRCS		:= ./main.c \
			./signals/signals.c \
			./pipe/pipe_main.c \
			./parsing/parsing.c \
			./parsing/parsing_2.c \
			./parsing/parsing_3.c \
			./builtins/echo/echo.c \
			./builtins/echo/echo_simple_quote.c \
			./builtins/echo/echo_double_quote.c \
			./builtins/echo/echo_2.c \
			./builtins/echo/dollar.c \
			./builtins/echo/dollar_n.c \
			./builtins/echo/dollar_double.c \
			./builtins/env/env_1.c \
			./builtins/env/env_2.c \
			./builtins/env/env_3.c \
			./builtins/redirection/right.c \
			./builtins/redirection/right_double.c \
			./builtins/builtin.c \
			./builtins/cd_project.c \
			./builtins/exit.c \
			./builtins/pwd.c

OBJS		:= $(SRCS:.c=.o)
BONUS		:= tahar
BONUSDIR	:= ./builtins
B_SOURCES	:= $(BONUSDIR)/env.c
B_OBJECTS	:= $(B_SOURCES:.c=.o)
HEADERS		:= -I $(HDRS) -I $(LIBFTDIR)/includes -I $(BONUSDIR)
LIBS		:= $(LIBFT) -lreadline -lncurses

NAME		:= minishell

all: $(INFOS) libft $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(INFOS):
	@$(MK) -p $(INFOS)

$(NAME): $(OBJS) $(HDRS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)**********************$(NC)"
	@echo "$(GREEN)* $(NAME) COMPILED *$(NC)"
	@echo "$(GREEN)**********************$(NC)"

bonus: $(BONUS)

$(BONUS): $(LIBS) $(B_OBJECTS)
	@$(CC) $(CFLAGS) $(B_OBJECTS) $(LIBS) $(HEADERS) -o $(BONUS)
	@echo "$(GREEN)**********************$(NC)"
	@echo "$(GREEN)*   BONUS COMPILED   *$(NC)"
	@echo "$(GREEN)**********************$(NC)"

libft: $(LIBFT)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFTDIR) bonus
	@echo "$(GREEN)**********************$(NC)"
	@echo "$(GREEN)*   LIBFT COMPILED   *$(NC)"
	@echo "$(GREEN)**********************$(NC)"

norme: $(INFOS)
	@$(NR) $(NRCFLAGS) $(SRCS) $(BONUSDIR)/*c > $(INFOS)/norme_infos.txt
	@$(NR) $(NRHFLAGS) $(HDRS)/* $(BONUSDIR)/*.h >> $(INFOS)/norme_infos.txt
	@echo "$(GREEN)**********************$(NC)"
	@echo "$(GREEN)*      NORME OK      *$(NC)"
	@echo "$(GREEN)**********************$(NC)"

push: fclean $(INFOS)
	@$(GADD) Makefile $(SRCS) $(HDRS) >> $(INFOS)/git_infos.txt 2>&1
	@$(GCMT) >> $(INFOS)/git_infos.txt 2>&1
	@$(GPUSH) >> $(INFOS)/git_infos.txt 2>&1
	@echo "$(GREEN)**********************$(NC)"
	@echo "$(GREEN)*  $(NAME) PUSHED  *$(NC)"
	@echo "$(GREEN)**********************$(NC)"

clean:
	@$(MAKE) -s -C $(LIBFTDIR) clean
	@$(RMF) $(OBJS) $(B_OBJECTS) ./*.o
	@echo "$(GREEN)**********************$(NC)"
	@echo "$(GREEN)*  DIRECTORY CLEANED *$(NC)"
	@echo "$(GREEN)**********************$(NC)"

fclean: clean
	@$(MAKE) -s -C $(LIBFTDIR) fclean
	@$(RMF) -r $(INFOS)
	@$(RMF) $(LIBFT) $(NAME) $(BONUS)

re: fclean all

.PHONY: re fclean clean all norme libmlx
