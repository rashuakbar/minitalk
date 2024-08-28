# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vimendes <vimendes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 22:05:09 by vimendes          #+#    #+#              #
#    Updated: 2024/08/28 10:00:25 by vimendes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCA =	./client.c \
		./utils.c 

SRCB =	./server.c \
		./utils.c
		
LIB = ./minitalk.h
OBJS = $(SRCA:.c=.o) $(SRCB:.c=.o)
		
all: 
		cc $(CFLAGS) $(SRCA) -I $(LIB) -o $(CLIENT)
		cc $(CFLAGS) $(SRCB) -I $(LIB) -o $(SERVER)
		
clean:  
		rm -rf $(OBJS)
		
fclean: clean
		rm -rf $(CLIENT) $(SERVER)
		
re:		fclean all
		