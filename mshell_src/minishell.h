/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:49:57 by vgribkov          #+#    #+#             */
/*   Updated: 2023/06/18 19:29:45 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_token
{
	char			**env;
	char			*token;
	struct s_token	*next;
}					t_token;


void	bi_env(t_token *token);

void	bi_pwd(void);

void	bi_echo(t_token *token);

void	bi_exit(t_token *token);

void	exec_1(t_token *token, char **env);

int	count_words_V(char const *s, char c);

char	**main_split_V(char *s, char c);

char	**ft_split_V(char *s, char c);

t_token	*ft_lstlast_token(t_token *lst);

void	ft_lstdelone_token(t_token *lst, void (*del)(char *));

void	ft_lstclear_token(t_token **lst, void (*del)(char *));

void	ft_lstadd_back_token(t_token **lst, t_token *new);

t_token	*ft_lstnew_token(char *token);

void	del_token(char *content);

void	printf_node(t_token *lst);

int	ft_lstsize_token(t_token *lst);

void	bi_cd(t_token *token);

#endif