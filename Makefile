NAME     = minishell
CFLAGS   = -Wall -Wextra -Werror -g #-fsanitize=address
RM       = rm -rf
LIBS     = -I./includes/ -I./readline/include

SRC = mshell_src
OBJ = obj
SUBDIRS = main #lexer utils execute builtins parser heredoc_redir error_handles 

SRC_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(SRC)/, $(dir)))
OBJ_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(OBJ)/, $(dir)))

SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
OBJS = $(subst $(SRC), $(OBJ), $(SRCS:.c=.o))
HEADER = includes/minishell.h

LIBFT_DIR = ./libft/

RDLINE        := readline
RDLINE_PATH   = $(addprefix $(shell pwd)/, $(RDLINE))
RDLINE_MAIN   = $(addprefix $(RDLINE), -main)
RDLINE_RESERV = $(addprefix $(RDLINE), -lib)
RDLINE_DIR    = ./$(RDLINE)/lib

all: readline $(NAME)

readline: Makefile
		make readline-util;

readline-util:
	@$(RM) $(RDLINE_RESERV)
	@cp -R $(RDLINE_MAIN) $(RDLINE_RESERV)
	@cd $(RDLINE_RESERV) && exec ./configure --prefix=${RDLINE_PATH}
	@make -C ./$(RDLINE_RESERV)
	@make -C ./$(RDLINE_RESERV) install
	@$(RM) $(RDLINE_RESERV)

$(NAME): $(HEADER) Makefile $(OBJS)
	@make -C $(LIBFT_DIR) all
	@cc -o $(NAME) $(OBJS) -g $(CFLAGS) $(LIBS) -L$(LIBFT_DIR) -lft -L$(RDLINE_DIR) -l$(RDLINE) -lncurses

$(OBJ)/%.o: $(SRC)/%.c $(HEADER)
	@mkdir -p $(OBJ) $(OBJ_DIR)
	@cc $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ)
fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@$(RM) $(RDLINE)
re: fclean all

.PHONY: all clean fclean re