#!/bin/bash

YES=y
NO=n
read -p "Do you want to create a new project ? (y/n) " REP

if [ $REP = $YES ]
then

	# creation du dossier projet et du dossier srcs
	read -p "What's the name of the project ? " PROJECT
	mkdir $PROJECT
	cd  $PROJECT
	mkdir srcs

	# creation du fichier auteur
	read -p "What's your login ? " LOGIN
	echo $LOGIN > auteur

	# creation du Makefile
	echo -e "NAME = $PROJECT\nCC = gcc\nOPTIONS = -c\nFLAGS = -Wall -Wextra -Werror\nSRCS =\nSRCSPATH = srcs\nOBJS = \$(SRCS:.c=.o)\nRM = rm -rf\n\nMAKEFLAGS = s\n\nall : \$(NAME)\n\n%.o : \$(SRCSPATH)/%.c\n\t@\$(CC) \$(FLAGS) -c \$< -o \$@\n\n\$(NAME) : \$(OBJS)\n\t@make -C ./libft/\n\t@\$(CC) \$(OBJS) ./libft/libft.a -o \$(NAME)\n\nclean :\n\t@\$(RM) \$(OBJS)\n\nfclean : clean\n\t@\$(RM) \$(NAME)\n\nre : clean all" > Makefile
	
	# copie de la libft
	cp -r ~/libft .
	echo "Success !"
fi
echo "Goodbye !"
