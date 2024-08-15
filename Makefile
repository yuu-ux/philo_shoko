# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/10 17:34:02 by ssoeno            #+#    #+#              #
#    Updated: 2024/08/10 20:48:18 by ssoeno           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c utils.c init.c threads.c monitor.c routine_actions.c
SRCPATH = $(addprefix ./src/, $(SRC))
OBJ = $(SRCPATH:.c=.o)
# SANITIZER = -fsanitize=thread

#default target
all: $(NAME)

#create static library
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(SANITIZER)

#clean
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: FLAGS += -g; $(MAKE) re

.PHONY: all clean fclean re debug