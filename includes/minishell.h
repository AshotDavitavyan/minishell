/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:49:57 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/28 15:33:20 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_shell	t_shell;

typedef struct s_token
{
	int					here_fd;

	int					err;
	int					here_doc_flag;
	char				**sep_arr;
	int					redir_flag_out;
	int					redir_flag_in;
	int					redir_flag_outout;
	char				**redir_fd_out;
	char				**redir_fd_in;
	char				**token;
	struct s_token		*next;
	t_shell				*shell;
}						t_token;

typedef struct s_token_small
{
	int						type;
	int						var_flag;
	char					*name;
	t_shell					*shell;
	struct s_token_small	*next;
	struct s_token_small	*prev;
}					t_token_small;

typedef struct s_shell
{
	int					fd[1000][2];
	char				**envex;
	t_token_small		*token_small;
	t_token				*token;
}				t_shell;

int						g_global_error;
int					kastil(char *user_input);
int					check(char *user_input, char type, int i, int todo);
int					after_quotes(char *user_input, char type);
int					ft_strchr_num(const char *s, int c);
int					ft_strnncmp(char **s1, char **s2, size_t n, int *to_return);
int					check_for_special_signs(t_token_small *tokens);
int					comp_vars_util(char **name, char **var_arr, int i, int j);
int					isnum(char **name);
int					single_dollar(char **name, char **new_name);
int					parse_tokens(t_token_small *tokens, t_token \
					**tokfin, t_token_small *head, t_token *token_save);
int					find_err(t_token *tokfin);
int					str_find(char **tokens);
int					heredoc(t_token_small **tokens, t_token **token_final);
int					add_redirs(t_token_small **tokens, t_token **tokfin);
int					intlen(int to_count);
int					env_len(char *str, char **name);
int					put_global_error(char **new_name, char **name_ptr);
int					check_echo(char *to_check);
int					qch_usd(char *user_input, int i);

char				*space_skip(char *user_input);
char				*put_spaces(char *user_input, int i, int size);
char				*alloc(char *u_i, char *input_new);
char				**add_fd(char **current, t_token_small *tokens,
						int size, char **to_return);
char				*move_env(char *env);
char				**hand_s(char *to_print, char *token, char **to_free);

void				before_quote(char *user_input, int pos, char **token);
void				tokenadd_back(t_token_small *token, t_token_small *to_add);
void				free_tokens(t_token_small	**tokens);
void				get_tokens(char *user_input, t_token_small **tokens, int i);
void				error(void);
void				handle_dollar_signs(t_token_small **tokens);
void				check_var(t_token_small **ptr, int dollar_index, int i);
void				put_vars(char *new_name,
						t_token_small **ptr, char *name_ptr, char *save);
void				free_big_tokens(t_token **tokens);
void				init_shell(t_token_small **tokens, t_shell **shell);
void				init_env(t_shell **shell, char **envp);
void				move_ptr(char **name);
void				util_dollar(char **new_name, char **name_ptr);
void				parse_tokens_util1(t_token **token_final,
						t_token_small *tokens);
void				pick_the_right_flag(t_token **tokfin,
						t_token_small **tokens);
void				arrcpy(char **to_be, char **current, char *to_add);
void				sighandler3(int signal);
void				sighandler2(int signal);
void				sighandler3(int signal);
void				check_spec_signs_four(t_token **tokfin, \
t_token_small **tokens);
void				check_spec_signs_three(t_token **tokfin, \
t_token_small **tokens);
void				check_spec_signs_one(t_token **tokfin, \
t_token_small **tokens);

//free_stuff
void				free_tokens(t_token_small	**tokens);
void				free_arr(char **to_free);
void				free_big_tokens(t_token **tokens);
//print_stuff
void				print_arr(char **to_print, char *name);
void				print_big_token(t_token *tokfin);
void				print_env(char **envp);
void				print_tokens(t_token_small *tokens);

t_token_small		*tokenadd_new(char *name, int type);
t_token_small		*create_token(t_token_small *token, char *name, int type);
t_token_small		*tokendelone(t_token_small *to_remove,
						t_token_small **tokens);
t_token_small		*reset_tokens(t_token **token_final,
						t_token *token_save, t_token_small *head);
t_token				*parse_tokens_util2(t_token **token_final,
						t_token_small *tokens);
t_token				**tokenfinaladd(t_token **str, t_token_small *tokens);
void				sighandler(int signum);
void				sighandler2(int signal);
void				sighandler_hd(int signum);
void				sighandler3(int signal);

int					bi_avail(t_token *token);

int					bi_env(t_shell *shell);

int					bi_pwd(void);

int					bi_echo(t_token *token);

int					bi_export1(t_shell *shell);

void				def_putstr(char *s);

void				my_putstr(char *str);

void				my_putstr(char *str);

int					bi_export2(t_shell *shell, char **arr, int i);

int					push_in_arr(t_shell *shell, char *str);

int					find_dup(t_shell *shell, char *str, int i);

int					bi_exit(t_token *token);

int					ft_is_num(char *str);

unsigned long long	atoulli(const char *str);

int					long_long_check(char *number);

int					bi_unset(t_shell *shell);

void				exec(t_shell *shell);

void				executing_one(t_shell *shell);

int					count_words_V(char const *s, char c);

char				**main_split_V(char *s, char c);

char				**ft_split_V(char *s, char c);

t_token				*ft_lstlast_token(t_token *lst);

void				ft_lstdelone_token(t_token *lst, void (*del)(char *));

void				ft_lstclear_token(t_token **lst, void (*del)(char *));

void				ft_lstadd_back_token(t_token **lst, t_token *new);

t_token				*ft_lstnew_token(char *token, t_shell *shell);

void				del_token(char *content);

void				printf_node(t_token *lst);

int					ft_lstsize_token(t_token *lst);

int					bi_cd(t_token *token);

void				change_new_pwd(t_shell *shell);

void				printf_arr(char **input);

int					ft_strlen_2d_arr(char **arr);

void				ft_free(char **arr);

int					ft_strcmp(char *str1, char *str2);

char				*true_path(char *argv, char **env);

void				redirector(t_token *token);

void				redirector_bi(t_token *token);

int					bi_execution(t_token *token);

void				close_all(t_token *token, int j);

void				redirector_bi(t_token *token);

void				here_doc_looper(t_token *token);

void				here_d(t_token *token, int j);

int					open_0(char *argv);

char				*str_to_lower(char *str);

void				openh_dup2(int fd);

void				exec_n(t_shell *shell);

void				error_no_dir(char *str);

void				fd_cd_print_status(char *cmd);

void				error_perm_denied(char *str);

int					change_old_pwd(t_shell *shell, char *arr);

char				*dup_bef_eq(char *str);

void				f_error(char *str);

void				do_pipes(t_shell *shell, int j);

int					count_exec(t_shell *shell);

void				pipes_dups(t_token *token, int j);

void				piping(t_token *token, int j, int i);

void				fork_failed_error(void);

int					unset_acheck(t_shell *shell, char *str);

void				help_exp(t_shell **shell, int i, char *arr);

char				*strdup_bez_pls(char *arr);

#endif
