/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:49:57 by vgribkov          #+#    #+#             */
/*   Updated: 2023/06/16 17:31:59 by vgribkov         ###   ########.fr       */
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
	char			*token;
	struct s_token	*next;
}					t_token;

typedef struct s_variables
{
	int	f1;
	int	f2;
	int	a;
	int	infile;
	int	outfile;
	int	fd[2];
}				t_variables;

void	bi_env(char **env);

void	bi_pwd(void);

void	bi_echo(t_token *token);

void	exec_1(t_token *token, char **env);

int	count_words_V(char const *s, char c);

char	**main_split_V(char *s, char c);

char	**ft_split_V(char *s, char c);

void	exec_n(t_token *token, char **env);

//------------------pipex_utils---------------------//

void	do_pipes(t_variables *variables);

void	f_error(void);

char	*path_finder(char **env);

void	fn_path(char **res_split, char *argv);

char	*true_path(char *argv, char **env);

//--------------------------------------------------//

#endif