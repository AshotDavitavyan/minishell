#include "minishell.h"

void    free_tokens(t_token_small	**tokens)
{
	t_token_small	*tmp;

	tmp = *tokens;
	if (!tmp)
		return ;
	while (*tokens != NULL)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->name);
		free(tmp);
	}
}

void	free_arr(char **to_free)
{
	char *ptr;
	
	if (to_free == NULL)
		return ;
	while(*to_free && to_free)
	{
		ptr = *to_free;
		to_free++;
		free(ptr);
	}
}

void	free_big_tokens(t_token **tokens)
{
	t_token	*ptr;
	while (*tokens != NULL)
	{
		ptr = (*tokens);
		free_arr((*tokens)->sep_arr);
		free_arr((*tokens)->redir_fd_out);
		free_arr((*tokens)->redir_fd_in);
		free((*tokens)->token);
		free(ptr);
		(*tokens) = (*tokens)->next;
	}
}