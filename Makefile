NAME = minishell

SRCS = main.c
OBJS = $(SRCS:.c=.o)

CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
LIBPFP = ./ft_printf/
LIBFTP = ./libft/
LIBPF = $(LIBPFP)libftprintf.a
LIBFT = $(LIBFTP)libft.a

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:  $(NAME) $(LIBPF) $(LIBFT)

$(NAME): $(OBJS) $(LIBPF) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBPF) $(LIBFT) -o $(NAME)

$(LIBPF):
	@make -C $(LIBPFP)

$(LIBFT):
	@make -C $(LIBFTP)

clean:
	$(RM) $(OBJS)
	@make clean -C $(LIBPFP)
	@make clean -C $(LIBFTP)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBPFP)
	@make fclean -C $(LIBFTP)

re: fclean all

reb: fclean bonus

.PHONY: all flean clean re

