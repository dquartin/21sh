# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dquartin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 12:05:37 by dquartin          #+#    #+#              #
#    Updated: 2018/03/01 13:18:46 by dquartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
OPTIONS = -c
SRCS = ft_puterror.c\
	   ft_countstr.c\
	   ft_strreplace.c\
	   ft_putcolor.c\
	   ft_putnbrcolornl_c.c\
	   ft_strjoindel.c\
	   ft_nbdigit_c.c\
	   ft_padding_c.c\
	   ft_realloc.c\
	   get_next_line.c\
	   ft_lstiter.c\
	   ft_putchar_fd.c\
	   ft_strdel.c\
	   ft_strncpy.c\
	   ft_atoi.c\
	   ft_lstmap.c\
	   ft_putendl.c\
	   ft_strdup.c\
	   ft_strnequ.c\
	   ft_bzero.c\
	   ft_lstnew.c\
	   ft_putendl_fd.c\
	   ft_strequ.c\
	   ft_strnew.c\
	   ft_isalnum.c\
	   ft_memalloc.c\
	   ft_putnbr.c\
	   ft_striter.c\
	   ft_strnstr.c\
	   ft_isalpha.c\
	   ft_memccpy.c\
	   ft_putnbr_fd.c\
	   ft_striteri.c\
	   ft_strrchr.c\
	   ft_isascii.c\
	   ft_memchr.c\
	   ft_putstr.c\
	   ft_strjoin.c\
	   ft_strsplit.c\
	   ft_isdigit.c\
	   ft_memcmp.c\
	   ft_putstr_fd.c\
	   ft_strlcat.c\
	   ft_strstr.c\
	   ft_isprint.c\
	   ft_memcpy.c\
	   ft_strcat.c\
	   ft_strlen.c\
	   ft_strsub.c\
	   ft_itoa.c\
	   ft_memdel.c\
	   ft_strchr.c\
	   ft_strmap.c\
	   ft_strtrim.c\
	   ft_lstadd.c\
	   ft_memmove.c\
	   ft_strclr.c\
	   ft_strmapi.c\
	   ft_tolower.c\
	   ft_lstdel.c\
	   ft_memset.c\
	   ft_strcmp.c\
	   ft_strncat.c\
	   ft_toupper.c\
	   ft_lstdelone.c\
	   ft_putchar.c\
	   ft_strcpy.c\
	   ft_strncmp.c\
	   ft_sqrt.c\
	   ft_pow.c\
	   ft_putnbr_base.c\
	   ft_itoa_base.c\
	   ft_touppercase.c\
	   ft_tolowercase.c\
	   ft_strnrstr.c
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

all: $(NAME)

%.o: %.c
	@echo ${Y}Compiling [$@]...${X}
	@$(CC) $(FLAGS) -c $< -o $@
	@printf ${UP}${CUT}

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[01;32mCompilation de la libft OK.\033[0m"

clean :
	@$(RM) $(OBJS)
	@echo "\033[01;31mSuppression des objets de la libft...\033[0m"

fclean:	clean
	@$(RM) $(NAME)
	@echo "\033[01;31mSuppression de l'executable libft.a...\033[0m"

re : fclean all
