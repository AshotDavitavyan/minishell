#ifndef MINISHELL_H
# define MINISHELL_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_shell t_shell;

typedef struct s_big_token
{
	int 			here_fd;

	int				here_doc_flag;
	char			**sep_arr;
	int				redirect_flag;
	char			**redirect_fd;
	char			*token;
	struct s_token	*next;
	t_shell 		*shell;
}					t_big_token;

typedef struct s_token
{
	int				type;
	char			*name;
	t_shell 		*shell;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	char		**envex;
	t_token		*token;
}				t_shell;

int		check(char *user_input, char type, int i, int todo);
int		after_quotes(char *user_input, char type);
int	ft_strchr_num(const char *s, int c);
int	ft_strnncmp(char **s1, char **s2, size_t n, int *to_return);

char	*space_skip(char *user_input);
char	*put_spaces(char *user_input);
char	*alloc(char *u_i, char *input_new);

void	before_quote(char *user_input, int pos, char **token);
void	tokenadd_back(t_token *token, t_token *to_add);
void    free_tokens(t_token	**tokens);
void	get_tokens(char *user_input, t_token **tokens, int i);
void	error(void);
void	handle_dollar_signs(t_token **tokens);
void	check_var(t_token **ptr, int dollar_index, int i);
void	put_vars(char *new_name, t_token **ptr);

t_token	*tokenadd_new(char *name, int type);
t_token *create_token(t_token *token, char *name, int type);

#endif