/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:49:57 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/17 15:08:05 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_shell t_shell;

typedef struct s_big_token
{
	int 				here_fd;

	int					here_doc_flag;
	char				**sep_arr;
	int					redir_flag_out;
	int					redir_flag_in;
	int					redir_flag_outout;
	char				**redir_fd_out;
	char				**redir_fd_in;
	char				*token;
	struct s_big_token	*next;
	t_shell 			*shell;
}						t_token_big;

typedef struct s_token
{
	int				type;
	char			*name;
	t_shell 		*shell;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_shell
{
	int			fd[1000][2];
	char		**envex;
	t_token		*big_token;
}				t_shell;

int		check(char *user_input, char type, int i, int todo);
int		after_quotes(char *user_input, char type);
int		ft_strchr_num(const char *s, int c);
int		ft_strnncmp(char **s1, char **s2, size_t n, int *to_return);
int		check_for_special_signs(t_token *tokens);

char	*space_skip(char *user_input);
char	*put_spaces(char *user_input);
char	*alloc(char *u_i, char *input_new);

char	**add_fd(char **current, t_token *tokens, int size, char **to_return);

void	before_quote(char *user_input, int pos, char **token);
void	tokenadd_back(t_token *token, t_token *to_add);
void    free_tokens(t_token	**tokens);
void	get_tokens(char *user_input, t_token **tokens, int i);
void	error(void);
void	handle_dollar_signs(t_token **tokens);
void	check_var(t_token **ptr, int dollar_index, int i);
void	put_vars(char *new_name, t_token **ptr);
void	free_arr(char **to_free);
void	free_big_tokens(t_token_big **tokens);
void	parse_tokens(t_token *tokens, t_token_big **token_final, t_token *head);
void	add_redirs(t_token **tokens, t_token_big **tokfin);
void	init_shell(t_token **tokens, t_shell **shell);
void	init_env(t_shell **shell, char **envp);


//free_stuff
void    free_tokens(t_token	**tokens);
void	free_arr(char **to_free);
void	free_big_tokens(t_token_big **tokens);
//print_stuff
void	print_arr(char **to_print, char *name);
void	print_big_token(t_token_big *tokfin);
void	print_env(char **envp);
void	print_tokens(t_token *tokens);

t_token	*tokenadd_new(char *name, int type);
t_token *create_token(t_token *token, char *name, int type);

t_token_big **tokenfinaladd(t_token_big **str, t_token *tokens);

int					global_error;

int				bi_avail(t_token *token);

int				bi_env(t_shell *shell);

int			bi_pwd(void);

int			bi_echo(t_token *token);

int			bi_export1(t_shell *shell);

void			def_putstr(char *s);

void			my_putstr(char *str);

void			my_putstr(char *str);

int			bi_export2(t_shell *shell, char **arr);

int			push_in_arr(t_shell *shell, char *str);

int				find_dup(t_shell *shell, char *str);

int			bi_exit(t_token *token);

int				ft_is_num(char *str);

unsigned long long	atoulli(const char *str);

int	long_long_check(char *number);

int	bi_unset(t_shell *shell);

void	exec(t_shell *shell);

void	executing_one(t_shell *shell);

int	count_words_V(char const *s, char c);

char	**main_split_V(char *s, char c);

char	**ft_split_V(char *s, char c);

t_token	*ft_lstlast_token(t_token *lst);

void	ft_lstdelone_token(t_token *lst, void (*del)(char *));

void	ft_lstclear_token(t_token **lst, void (*del)(char *));

void	ft_lstadd_back_token(t_token **lst, t_token *new);

t_token	*ft_lstnew_token(char *token, t_shell *shell);

void	del_token(char *content);

void	printf_node(t_token *lst);

int		ft_lstsize_token(t_token *lst);

int	bi_cd(t_token *token);

void	change_old_pwd(t_shell *shell);

void	change_new_pwd(t_shell *shell);

void	printf_arr(char **input);

int		ft_strlen_2d_arr(char **arr);

void	ft_free(char **arr);

int		ft_strcmp(char *str1, char *str2);

char	*true_path(char *argv, char **env);

void	redirector(t_token *token);

void	redirector_bi(t_token *token);

int		bi_execution(t_token *token);

void	close_all(t_token *token, int j);

void	redirector_bi(t_token *token);

void	here_doc_looper(t_token *token);

void	here_d(t_token *token, int j);

int	open_0(char *argv);

#endif