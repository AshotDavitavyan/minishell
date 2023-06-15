NAME = minishell
SRC_PATH = mshell_src
OBJ_PATH = obj
SRCS = $(addprefix $(SRC_PATH)/, built_ins.c V_main.c exec.c)
OBJS = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))

CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
LIBFTP = ./libft/
LIBFT = $(LIBFTP)libft.a

all: $(NAME) $(LIBPF) $(LIBFT)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@ make -C $(LIBFTP)

clean:
	@$(RM) $(OBJ_PATH)
	@make clean -C $(LIBFTP)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFTP)

re: fclean all

.PHONY: all fclean clean re
