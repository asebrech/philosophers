# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/23 16:13:10 by asebrech          #+#    #+#              #
#    Updated: 2021/10/07 13:59:28 by asebrech         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEADER = includes_bonus
NAME = philo_bonus
RM = rm -rf
SRC =	srcs_bonus/main_bonus.c	\
		srcs_bonus/utiles_bonus.c \
		srcs_bonus/philosophers_bonus.c	\
		srcs_bonus/philosophers_1_bonus.c	
OBJ = $(SRC:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $(<:.c=.o)

all : $(NAME)

bonus : all

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -pthread -I$(HEADER) $(OBJ) -o $(NAME)

clean :
	$(RM) */*.o

fclean : clean
	$(RM) $(NAME)


re : fclean all

.PHONY : all clean fclean re bonus