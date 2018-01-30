# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dquartin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/06 17:31:58 by dquartin          #+#    #+#              #
#    Updated: 2018/01/29 17:01:34 by hlely            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CC = gcc
OPTIONS = -c
FLAGS = -Wall -Wextra -Werror
SRCS = $(PARSEPATH)analyse.c\
	   $(MAINPATH)an_other_one.c\
	   $(ARROWPATH)arrow.c\
	   $(ARROWPATH)arrow_control.c\
	   $(ARROWPATH)arrow_move.c\
	   $(PARSEPATH)ast.c\
	   $(LINEPATH)call_fork.c\
	   $(LINEPATH)copy_n_paste.c\
	   $(FREEPATH)delete.c\
	   $(LINEPATH)environ.c\
	   $(REDIRPATH)heredoc.c\
	   $(HISTORYPATH)history.c\
	   $(HISTORYPATH)history_bis.c\
	   $(CDPATH)ft_cd.c\
	   $(CDPATH)ft_cd_del.c\
	   $(CDPATH)ft_cd_options.c\
	   $(BUILTINPATH)ft_echo.c\
	   $(BUILTINPATH)ft_env.c\
	   $(BUILTINPATH)ft_getenv.c\
	   $(HISTORYPATH)ft_list.c\
	   $(PARSEPATH)ft_major.c\
	   $(LINEPATH)ft_putin.c\
	   $(BUILTINPATH)ft_setenv.c\
	   $(SPLITPATH)ft_splitall.c\
	   $(SPLITPATH)ft_splitwhite.c\
	   $(BUILTINPATH)ft_unsetenv.c\
	   $(FREEPATH)free_index.c\
	   $(MAINPATH)main.c\
	   $(MAINPATH)main_bis.c\
	   $(LINEPATH)move.c\
	   $(MAINPATH)other_main.c\
	   $(QUOTEPATH)parse_quote.c\
	   $(LINEPATH)prompt_char.c\
	   $(QUOTEPATH)quotes.c\
	   $(QUOTEPATH)quotes_del.c\
	   $(REDIRPATH)redirection.c\
	   $(REDIRPATH)redirection_bis.c\
	   $(REDIRPATH)redirection_other.c\
	   $(LINEPATH)select_mode.c\
	   $(LINEPATH)signal.c\
	   $(COMPLETIONPATH)completion.c\
	   $(COMPLETIONPATH)complete_line.c\
	   $(COMPLETIONPATH)get_entry.c\
	   $(LSTPATH)ft_lst_add_end.c
SRCPATH = srcs
ARROWPATH = srcs/arrow/
MAINPATH = srcs/main/
CDPATH = srcs/builtin/cd/
BUILTINPATH = srcs/builtin/
HISTORYPATH = srcs/history/
REDIRPATH = srcs/redir/
QUOTEPATH = srcs/quote/
FREEPATH = srcs/free/
SPLITPATH = srcs/split/
PARSEPATH = srcs/parse/
LINEPATH = srcs/line/
COMPLETIONPATH = srcs/completion/
LSTPATH	= srcs/lst/
OBJS = $(SRCS:.c=.o)
	RM = rm -rf

MAKEFLAGS = s

all : $(NAME)

%.o: %.c
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
