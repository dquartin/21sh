# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dquartin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/06 17:31:58 by dquartin          #+#    #+#              #
#    Updated: 2018/03/01 13:38:32 by dquartin         ###   ########.fr        #
#    Updated: 2018/02/05 17:56:51 by dquartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CC = gcc
OPTIONS = -c
FLAGS = -Wall -Wextra -Werror
SRCS = $(ARROWPATH)arrow.c\
	   $(ARROWPATH)arrow_control.c\
	   $(ARROWPATH)arrow_move.c\
	   $(BUILTINPATH)alias.c\
	   $(BUILTINPATH)alias_bis.c\
	   $(BUILTINPATH)cmd_history.c\
	   $(BUILTINPATH)ft_echo.c\
	   $(BUILTINPATH)ft_env.c\
	   $(BUILTINPATH)ft_env_bis.c\
	   $(BUILTINPATH)ft_getenv.c\
	   $(BUILTINPATH)ft_setenv.c\
	   $(BUILTINPATH)ft_unsetenv.c\
	   $(BUILTINPATH)ft_unsetenv_bis.c\
	   $(BUILTINPATH)remove_alias.c\
	   $(CDPATH)ft_cd.c\
	   $(CDPATH)ft_cd_bis.c\
	   $(CDPATH)cd_return.c\
	   $(CDPATH)ft_cd_del.c\
	   $(CDPATH)ft_cd_options.c\
	   $(CDPATH)ft_cd_option_bis.c\
	   $(CDPATH)normalize.c\
	   $(FREEPATH)delete.c\
	   $(FREEPATH)delete_alias.c\
	   $(FREEPATH)delete_tree.c\
	   $(FREEPATH)free_index.c\
	   $(HISTORYPATH)ft_list.c\
	   $(HISTORYPATH)history.c\
	   $(HISTORYPATH)history_bis.c\
	   $(LINEPATH)call_fork.c\
	   $(LINEPATH)copy_n_paste.c\
	   $(LINEPATH)ft_putin.c\
	   $(LINEPATH)move.c\
	   $(LINEPATH)prompt_char.c\
	   $(LINEPATH)select_mode.c\
	   $(LINEPATH)signal.c\
	   $(LSTPATH)ft_lst_add_end.c\
	   $(MAINPATH)an_other_one.c\
	   $(MAINPATH)exit.c\
	   $(MAINPATH)main.c\
	   $(MAINPATH)main_bis.c\
	   $(MAINPATH)other_main.c\
	   $(MAINPATH)prompt.c\
	   $(MAINPATH)waitall.c\
	   $(PARSEPATH)analyse.c\
	   $(PARSEPATH)ast.c\
	   $(PARSEPATH)ast_bis.c\
	   $(PARSEPATH)ft_major.c\
	   $(REDIRPATH)heredoc.c\
	   $(SPLITPATH)ft_splitall.c\
	   $(SPLITPATH)ft_splitwhite.c\
	   $(PARSEPATH)parse_alias.c\
	   $(QUOTEPATH)parse_quote.c\
	   $(QUOTEPATH)quotes.c\
	   $(QUOTEPATH)quotes_del.c\
	   $(REDIRPATH)redirection.c\
	   $(REDIRPATH)redirection_bis.c\
	   $(REDIRPATH)redirection_other.c
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
LSTPATH	= srcs/lst/
OBJS = $(SRCS:.c=.o)
RM = rm -rf

MAKEFLAGS = s

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all : $(NAME)

%.o: %.c
	@echo ${Y}Compiling [$@]...${X}
	@$(CC) $(FLAGS) -c $< -o $@
	@printf ${UP}${CUT}

$(NAME) : $(OBJS)
	@make -C ./libft/
	@$(CC) -ltermcap $(OBJS) ./libft/libft.a -o $(NAME)
	@echo "\033[01;32mCompilation 21sh OK.✅\033[0m"

clean :
	@$(RM) $(OBJS)
	@echo "\033[01;31mSuppression des objest OK.🚮\033[0m"

fclean : clean
	@$(RM) $(NAME)
	@echo "\033[01;31mSuppression de l'executable OK.🚮\033[0m"

re : fclean all

.PHONY: all re fclean clean
