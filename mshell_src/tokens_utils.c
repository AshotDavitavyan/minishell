#include "minishell.h"

t_token	*tokenadd_new(char *name, int type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	token->name = name;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	tokenadd_back(t_token *token, t_token *to_add)
{
	t_token *save;
	save = token;
	while (token->next != NULL)
		token = token->next;
	token->next = to_add;
	token->next->prev = token;
	token = save;
}

t_token *create_token(t_token *token, char *name, int type)
{
	if (token == NULL)
		return (tokenadd_new(name, type));
	else
	{
		tokenadd_back(token, tokenadd_new(name, type));
		return (token);
	}
}
