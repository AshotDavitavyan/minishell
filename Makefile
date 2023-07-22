NAME     = minishell
CFLAGS   = -Wall -Wextra -Werror -g #-fsanitize=address
RM       = rm -rf
LIBS     = -I./includes/ -I./readline/include

SRC = mshell_src
OBJ = obj
SUBDIRS = lexer utils execute builtins parser main heredoc_redir error_handles

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

RESET  = \033[0m
RED    = \033[31;1m
GREEN  = \033[32;1m
YELLOW = \033[33;1m

all: readline $(NAME)
	@echo > /dev/null

readline: Makefile
	@if [ -d $(RDLINE) ]; then \
		make READLINE_READY; \
	else \
		make readline-util; \
	fi

readline-util:
	@echo "${YELLOW}Please wait until program compiling...${RESET}"
	@$(RM) $(RDLINE_RESERV)
	@cp -R $(RDLINE_MAIN) $(RDLINE_RESERV)
	@cd $(RDLINE_RESERV) && exec ./configure --prefix=${RDLINE_PATH}
	@make -C ./$(RDLINE_RESERV)
	@make -C ./$(RDLINE_RESERV) install
	@$(RM) $(RDLINE_RESERV)
	@make READLINE_READY

$(NAME): $(HEADER) Makefile $(OBJS)
	@make WAIT_COMPILE_MSG
	@echo "${GREEN}Compiling LIBFT...${RESET}"
	@make -C $(LIBFT_DIR) all
	@cc -o $(NAME) $(OBJS) -g $(CFLAGS) $(LIBS) -L$(LIBFT_DIR) -lft -L$(RDLINE_DIR) -l$(RDLINE) -lncurses 
	@make DONE_MSG

$(OBJ)/%.o: $(SRC)/%.c $(HEADER)
	@mkdir -p $(OBJ) $(OBJ_DIR)
	@echo "${YELLOW}Compiling $<${RESET}"
	@cc $(CFLAGS) $(LIBS) -c $< -o $@

clean: DELETE_OBJ_MSG
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ)
fclean: clean DELETE_PROGRAM_MSG
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@$(RM) $(RDLINE)
re: fclean all

READLINE_READY:
	@echo "${GREEN}Readline is Ready!${RESET}" > /dev/null
WAIT_COMPILE_MSG:
	@echo "${YELLOW}Please wait until program compiling...${RESET}"
DONE_MSG:
	@echo "${GREEN}>>> Minishell is ready <<<${RESET}"
DELETE_OBJ_MSG:
	@echo "${RED}Object files deleting...${RESET}"
DELETE_PROGRAM_MSG:
	@echo "${RED}Minishell is deleting...${RESET}"

.PHONY: all clean fclean re