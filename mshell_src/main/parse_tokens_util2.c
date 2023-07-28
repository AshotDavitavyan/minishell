#include "../../includes/minishell.h"

t_token_small	*reset_tokens(t_token **token_final, \
t_token *token_save, t_token_small *head)
{
	*token_final = token_save;
	return (head);
}

void	parse_tokens_util1(t_token **token_final, t_token_small *tokens)
{
	token_final = tokenfinaladd(token_final, tokens);
	*token_final = (*token_final)->next;
}

t_token	*parse_tokens_util2(t_token **token_final, t_token_small *tokens)
{
	token_final = tokenfinaladd(token_final, tokens);
	return (*token_final);
}
