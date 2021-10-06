# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/23 16:13:10 by asebrech          #+#    #+#              #
#    Updated: 2021/10/06 11:44:29 by asebrech         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEADER = includes_bonus
NAME = philo_bonus
RM = rm -rf
SRC =	srcs_bonus/main_bonus.c	\
		srcs_bonus/utiles_bonus.c \
		srcs_bonus/philosophers_bonus.c	
SRCB =

ifdef WHITH_BONUS
	OBJ = $(SRC:.c=.o)
else
	OBJ = $(SRC:.c=.o)
endif

.c.o :
	$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $(<:.c=.o)

all : $(NAME)

bonus :
	@make WHITH_BONUS=1 all

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -pthread -I$(HEADER) $(OBJ) -o $(NAME)

clean :
	$(RM) */*.o

fclean : clean
	$(RM) $(NAME)


re : fclean all

.PHONY : all clean fclean re bonus