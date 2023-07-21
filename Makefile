NAME = minishell
SRC_PATH = mshell_src
OBJ_PATH = obj
SRCS = $(addprefix $(SRC_PATH)/, V_main.c main.c tokens.c tokens_utils.c tokens_utils2.c count_size.c alloc_usr_input.c \
env1.c env_2.c env_utils.c print_stuff.c parse_tokens.c parse_tokens2.c free_stuff.c built_ins1.c built_ins2.c exec1.c exit_utils.c export_utils.c custom_putstr.c cd_utils.c exec2.c bi_checker.c redirect.c)
OBJS = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))

RLDIR = ./readline-main
RL_A = $(RLDIR)/libreadline.a
CC = cc
RM = rm -rf
LIBFTP = ./libft/
LIBFT = $(LIBFTP)libft.a

CFLAGS = -Wall -Werror -Wextra -I$(RLDIR) -g #-fsanitize=address
LIBS = -lreadline  -lncurses -L$(RLDIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(RL_A)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@ make -C $(LIBFTP)

$(RL_A):
	@cd $(RLDIR) && exec ./configure
	@make -C $(RLDIR)

clean:
	@$(RM) $(OBJ_PATH)
	@make clean -C $(LIBFTP)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFTP)

re: fclean all

.PHONY: all fclean clean re
