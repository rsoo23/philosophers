# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 15:06:43 by rsoo              #+#    #+#              #
#    Updated: 2023/06/12 15:06:43 by rsoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 
#-pthread -fsanitize=thread
RM = rm -rf

SRCS = main_bonus input_check_bonus philo_states_bonus utils_1_bonus utils_2_bonus
SRCS_CFILES = $(addsuffix .c, $(SRCS))
OBJS = $(SRCS_CFILES:.c=.o)

%.o: %.c ./Makefile
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY = clean fclean re all
