# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 18:14:09 by ogorfti           #+#    #+#              #
#    Updated: 2023/02/18 19:29:35 by ogorfti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_M = philo.c\

OBJS_M = $(SRC_M:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

hd = philo.h

all : $(NAME)

%.o : %.c $(hd)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS_M) 
		$(CC) $(CFLAGS) $(OBJS_M) -o $(NAME)

clean :
		$(RM) $(OBJS_M)

fclean : clean
		$(RM) $(NAME)

re: fclean all
