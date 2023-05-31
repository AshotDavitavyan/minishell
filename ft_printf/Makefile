# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 12:13:29 by adavitav          #+#    #+#              #
#    Updated: 2023/05/31 14:19:26 by vgribkov         ###   ########.fr        #
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

OBJS = $(addprefix obj/,$(SRCS:.c=.o))
OBJ_PATH = obj/

FLAGS = -Wall -Werror -Wextra

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_PATH)%.o: %.c
	cc $(FLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

clean:
	rm -rf $(OBJ_PATH)
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)
