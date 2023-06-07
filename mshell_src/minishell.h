#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

// typedef struct s_token
// {
// 	t_token	*before;
// 	int		type;
// 	char 	*flags;
// 	char 	*name;
// 	t_token	*next;
// }	t_token;

void	bi_env(int argc ,char **argv, char **env);

void	bi_pwd(void);

#endif