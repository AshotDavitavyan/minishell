# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adavitav <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 12:13:29 by adavitav          #+#    #+#              #
#    Updated: 2023/02/21 17:17:43 by adavitav         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = 	ft_putchar.c \
		ft_putstr.c \
		ft_putnbr.c \
		ft_putnbr_u.c \
		ft_printf.c \
		ft_strdup.c \
		ft_print_p.c \
		hex_check_lc.c \
		hex_check_uc.c \

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -c $(SRCS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)
