# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malleman <malleman@42lausanne.ch>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 13:39:48 by malleman          #+#    #+#              #
#    Updated: 2023/03/15 17:05:37 by malleman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#-------------------------- SOURCES -------------------------------------------#
SRCS_S =	serveur.c
SRCS_C =	client.c

#--------------------------	VARIABLES -----------------------------------------#
NAME		= 
SERVEUR 	= serveur
CLIENT 		= client

OBJS_S		= ${SRCS_S:.c=.o}
OBJS_C		= ${SRCS_C:.c=.o}

CC			= gcc
CFLAGSDDBUG	= -Wall -Wextra =Werror -I. -Iincludes -g 
CFLAGS		= -Wall -Wextra -Werror -I. -Iincludes

#-------------------------- COMMANDES -----------------------------------------#
.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${SERVEUR}: ${OBJS_S}
	make -C ./libft
	${CC} ${CLFAGS} ${SRCS_S} ${LIBFT} -o ${SERVEUR} -Llibft -lft

${CLIENT}: ${OBJS_C}
	make -C ./libft
	${CC} ${CLFAGS} ${SRCS_C} ${LIBFT} -o ${CLIENT} -Llibft -lft

all: 	${SERVEUR} ${CLIENT}

clean :
		
		rm -f ${OBJS_C} ${OBJS_S}
		make clean -C ./libft

fclean : clean
		rm -f ${CLIENT} ${SERVEUR}
		make fclean -C ./libft

re: 	fclean all

.PHONY: all clean fclean re
