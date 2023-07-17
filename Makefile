NAME = minishell
SRC_PATH = mshell_src
OBJ_PATH = obj
SRCS = $(addprefix $(SRC_PATH)/, main.c tokens.c tokens_utils.c tokens_utils2.c count_size.c alloc_usr_input.c \
env.c env_2.c env_utils.c print_stuff.c parse_tokens.c parse_tokens2.c free_stuff.c)
#built_ins1.c built_ins2.c V_main.c exec1.c exit_utils.c export_utils.c custom_putstr.c cd_utils.c exec2.c bi_checker.c redirect.c)
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
