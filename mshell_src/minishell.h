/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:49:57 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/12 13:34:22 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct s_token
{
	int 			here_fd;

	int				here_doc_flag;
	char			**sep_arr;
	int				redirect_flag;
	char			**redirect_fd;
	char			*token;
	struct s_token	*next;
	t_shell 		*shell;
}					t_token;

typedef struct s_shell
{
	int			fd[1000][2];
	char		**envex;
	t_token		*token;
}				t_shell;

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

void	executing_one(char *argvv, char **file, char **env, t_shell *shell);

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

void	redirector(t_token *token);

void	redirector_bi(t_token *token);

void	here_doc_looper(t_token *token);

void	here_d(t_token *token, int j);

int	open_0(char *argv);

#endif