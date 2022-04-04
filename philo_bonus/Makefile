# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 19:37:01 by hakim             #+#    #+#              #
#    Updated: 2022/04/04 18:24:48 by hakim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = philo_bonus
SRCS =	srcs/philosopher_bonus.c \
		srcs/life_of_philosophers_bonus.c \
        srcs/initializers_bonus.c \
        srcs/free_time_bonus.c \
        srcs/utils_bonus.c
OBJS = $(SRCS:%.c=%.o)

INCLUDES = -I./

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all clean re bonus
