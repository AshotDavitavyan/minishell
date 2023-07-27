#include "../../includes/minishell.h"

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
	char	*ptr;
	char	**save;
	
	if (to_free == NULL)
		return ;
	save = to_free;

	while(*to_free != NULL && to_free)
	{
		ptr = *to_free;
		to_free++;
		free(ptr);
	}
	*to_free = ft_strdup("bussing");
	free(*to_free);
	free(save);
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
		free_arr((*tokens)->token);
		free(ptr);
		(*tokens) = (*tokens)->next;
	}
}