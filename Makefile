# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 16:08:03 by ssanei            #+#    #+#              #
#    Updated: 2024/09/04 21:22:44 by ssanei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Werror -Wextra -g -pthread

SRCS = 	philo.c \
		checker.c \
		init_all_data.c \
		philos_actions.c \
		utils.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

	
$(OBJ): %.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	cc $(CFLAGS) -o $@ $(OBJ) -pthread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
