# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dquartin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/06 17:31:58 by dquartin          #+#    #+#              #
#    Updated: 2018/01/08 12:55:21 by dquartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CC = gcc
OPTIONS = -c
FLAGS = -Wall -Wextra -Werror
SRCS = ft_splitall.c\
	   ft_echo.c\
	   ft_env.c\
	   ft_cd.c\
	   ft_setenv.c\
	   ft_getenv.c\
	   ft_unsetenv.c\
	   main.c\
	   delete.c\
	   ft_splitwhite.c\
	   call_fork.c\
	   move.c\
	   ft_putin.c\
	   arrow_move.c\
	   arrow_control.c\
	   arrow.c\
	   ft_list.c\
	   history.c\
	   select_mode.c\
	   copy_n_paste.c\
	   prompt_char.c\
	   ast.c
SRCPATH = srcs
OBJS = $(SRCS:.c=.o)
RM = rm -rf

MAKEFLAGS = s

all : $(NAME)

%.o: $(SRCPATH)/%.c
	    @$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
		@make -C ./libft/
		@$(CC) -ltermcap $(OBJS) ./libft/libft.a -o $(NAME)
		@echo "\033[01;32mCompilation OK.✅\033[0m"

clean :
		@$(RM) $(OBJS)
		@echo "\033[01;31mSuppression des objest OK.🚮\033[0m"

fclean : clean
		@$(RM) $(NAME)
		@echo "\033[01;31mSuppression de l'executable OK.🚮\033[0m"

re : fclean all
