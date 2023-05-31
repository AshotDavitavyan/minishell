NAME = minishell

SRCS = main.c

OBJ = $(SRCS:.c=.o)

OBJ_PATH = obj/
SRC_PATH = ./
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
LIBPFP = ./ft_printf/
LIBFTP = ./libft/
LIBPF = $(LIBPFP)libftprintf.a
LIBFT = $(LIBFTP)libft.a

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ_PATH) $(NAME) $(LIBPF) $(LIBFT)

$(NAME): $(OBJS) $(LIBPF) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBPF) $(LIBFT) -o $(NAME)

$(LIBPF):
	@make -C $(LIBPFP)

$(LIBFT):
	@make -C $(LIBFTP)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

clean:
	$(RM) $(OBJ_PATH)
	@make clean -C $(LIBPFP)
	@make clean -C $(LIBFTP)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBPFP)
	@make fclean -C $(LIBFTP)

re: fclean all

reb: fclean bonus

.PHONY: all flean clean re

