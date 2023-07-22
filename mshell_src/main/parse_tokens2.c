#include "minishell.h"

void	arrcpy(char **to_be, char **current, char *to_add)
{
	int i;

	i = 0;
	while (*current)
	{
		to_be[i] = ft_strdup(*current);
		i++;
		current++;
	}
	to_be[i++] = ft_strdup(to_add);
	to_be[i] = NULL;
}

int	check_for_special_signs(t_token_small *tokens)
{
	if (ft_strnstr(tokens->name, "<", 1) && ft_strlen(tokens->name) == 1 && tokens->var_flag == 0)
		return (1);
	else if (ft_strnstr(tokens->name, "<<", 2) && ft_strlen(tokens->name) == 2 && tokens->var_flag == 0)
		return (2);
	else if (ft_strnstr(tokens->name, ">", 1) && ft_strlen(tokens->name) == 1 && tokens->var_flag == 0)
		return (3);
	else if (ft_strnstr(tokens->name, ">>", 2) && ft_strlen(tokens->name) == 2 && tokens->var_flag == 0)
		return (4);
	else if (ft_strnstr(tokens->name, "|", 1) && ft_strlen(tokens->name) == 1 && tokens->var_flag == 0)
		return (5);
	return (0);
}

char	**add_fd(char **current, t_token_small *tokens, int size, char **to_return)
{
	char	**ptr;

	ptr = current;
	if (tokens == NULL)
		error();
	if (check_for_special_signs(tokens) != 0 && tokens->type == 0)
		error();
	if (current == NULL)
	{
		to_return = (char **)malloc(2 * sizeof(char *));
		to_return[0] = ft_strdup(tokens->name);
		to_return[1] = NULL;
	}
	else
	{
		while (*ptr)
		{
			ptr++;
			size++;
		}
		to_return = (char **)malloc((size + 2) * sizeof(char *));
		arrcpy(to_return, current, tokens->name);
		free_arr(current);
	}
	return (to_return);
}

void	add_redirs(t_token_small **tokens, t_token **tokfin)
{
	while (*tokens != NULL)
	{
		if (check_for_special_signs(*tokens) == 1)
		{
			(*tokfin)->redir_flag_in = 1;
			*tokens = (*tokens)->next;
			(*tokfin)->redir_fd_in = add_fd((*tokfin)->redir_fd_in, *tokens, 0, NULL);
		}
		else if (check_for_special_signs(*tokens) == 3)
		{
			(*tokfin)->redir_flag_out = 1;
			*tokens = (*tokens)->next;
			(*tokfin)->redir_fd_out = add_fd((*tokfin)->redir_fd_out, *tokens, 0, NULL);
		}
		else if (check_for_special_signs(*tokens) == 4)
		{
			(*tokfin)->redir_flag_outout = 1;
			*tokens = (*tokens)->next;
			(*tokfin)->redir_fd_out = add_fd((*tokfin)->redir_fd_out, *tokens, 0, NULL);
		}
		else
			return ;
		(*tokens) = (*tokens)->next;
	}
}

t_token **tokenfinaladd(t_token **str, t_token_small *tokens)
{
	t_token	*to_add;

	to_add = (t_token *)malloc(sizeof(t_token));
	to_add->here_fd = 0;
	to_add->here_doc_flag = 0;
	to_add->sep_arr = NULL;
	to_add->redir_flag_out = 0;
	to_add->redir_flag_in = 0;
	to_add->redir_flag_outout = 0;
	to_add->redir_fd_out = NULL;
	to_add->redir_fd_in = NULL;
	to_add->token = NULL;
	to_add->next = NULL;
	to_add->shell = tokens->shell;

	if (*str != NULL)
		(*str)->next = to_add;
	else
		(*str) = to_add;
	return (str);
}