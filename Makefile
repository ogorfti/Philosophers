# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 18:14:09 by ogorfti           #+#    #+#              #
#    Updated: 2023/04/01 23:32:25 by ogorfti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_M = philo.c init.c utils.c check_arg.c routine.c free.c\

OBJS_M = $(SRC_M:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror 
#-fsanitize=thread -g
LDFLAGS = -pthread

#should remove -pthread

RM = rm -f

hd = philo.h

#should remove clean

all : $(NAME) clean

%.o : %.c $(hd)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS_M) 
		$(CC) $(CFLAGS) $(OBJS_M) $(LDFLAGS) -o $(NAME)

clean :
		$(RM) $(OBJS_M)

fclean : clean
		$(RM) $(NAME)

re: fclean all
