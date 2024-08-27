# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 16:08:03 by ssanei            #+#    #+#              #
#    Updated: 2024/08/27 19:33:30 by ssanei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Werror -Wextra -g -pthread

SRS = 	main.c \
		checker.c \
		init_all_data.c \
		philos_actions.c \
		handle_safe_functions.c \
		utils.c

OBJ = $(SRS:.c=.o)

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
