# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alois <alois@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/23 16:13:10 by asebrech          #+#    #+#              #
#    Updated: 2021/09/22 12:52:00 by alois            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEADER = includes
NAME = philosophers
RM = rm -rf
SRC =	srcs/main.c	\
		srcs/philosophers.c	
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
	$(CC) $(CFLAGS) -I$(HEADER) $(OBJ) -o $(NAME)

clean :
	$(RM) */*.o

fclean : clean
	$(RM) $(NAME)


re : fclean all

.PHONY : all clean fclean re bonus