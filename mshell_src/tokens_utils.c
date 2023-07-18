#include "minishell.h"

t_token_small	*tokenadd_new(char *name, int type)
{
	t_token_small *token;

	token = malloc(sizeof(t_token_small));
	token->name = name;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	tokenadd_back(t_token_small *token, t_token_small *to_add)
{
	t_token_small *save;
	save = token;
	while (token->next != NULL)
		token = token->next;
	token->next = to_add;
	token->next->prev = token;
	token = save;
}

t_token_small *create_token(t_token_small *token, char *name, int type)
{
	if (token == NULL)
		return (tokenadd_new(name, type));
	else
	{
		tokenadd_back(token, tokenadd_new(name, type));
		return (token);
	}
}
