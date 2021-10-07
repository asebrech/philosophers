# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/23 16:13:10 by asebrech          #+#    #+#              #
#    Updated: 2021/10/07 13:58:13 by asebrech         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEADER = includes
NAME = philo
RM = rm -rf
SRC =	srcs/main.c	\
		srcs/utiles.c \
		srcs/philosophers.c	
OBJ = $(SRC:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $(<:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -pthread -I$(HEADER) $(OBJ) -o $(NAME)

clean :
	$(RM) */*.o

fclean : clean
	$(RM) $(NAME)


re : fclean all

.PHONY : all clean fclean re