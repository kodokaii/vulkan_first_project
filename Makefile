# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kodokai <kodokai.featheur@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 00:51:17 by kodokai           #+#    #+#              #
#    Updated: 2023/02/19 19:21:07 by kodokai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra
PATH_SRC = ./src/
PATH_LIB = ./lib/
HEAD = ./include/
MAIN = main.c
EXEC = vulkan_project
DEBUGGER = ddd
SRCS = $(wildcard $(PATH_SRC)*.c)
LIBS = $(wildcard $(PATH_LIB)*.a) -lglfw -lvulkan
OBJS = $(SRCS:.c=.o)
MAIN_O = $(MAIN:.c=.o)

all: $(EXEC)

debug: debug_flags $(EXEC) 
	$(DEBUGGER) debug

debug_flags:
	$(eval FLAGS += -g)
	$(eval EXEC = debug)

$(EXEC): $(OBJS) $(MAIN_O)
	$(CC) $(FLAGS) -I $(HEAD) $(MAIN_O) $(OBJS) $(LIBS) -o $(EXEC) 

%.o: %.c
	$(CC) $(FLAGS) -c -I $(HEAD) $< -o $@
	
clean:
	rm -f $(OBJS) $(MAIN_O)

fclean: clean
	rm -f $(EXEC) debug

re: fclean all

.PHONY:		all debug clean fclean re
