#include "minishell.h"

t_token_small	*tokendelone(t_token_small *to_remove, t_token_small **tokens)
{
	t_token_small	*bus;
	t_token_small	*bul;

	if (to_remove->prev != NULL)
	{
		bus = to_remove->prev;
		bul = to_remove->next;
		free(to_remove->name);
		free(to_remove);
		bus->next = bul;
		if (bul != NULL)
			bul->prev = bus;
		return (bul);
	}
	else
	{
		bus = to_remove->next;
		if (bus != NULL)
			bus->prev = NULL;
		free(to_remove->name);
		free(to_remove);
		*tokens = bus;
		return (bus);
	}
}

t_token_small	*tokenadd_new(char *name, int type)
{
	t_token_small *token;

	token = malloc(sizeof(t_token_small));
	token->name = name;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	token->var_flag = 0;
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
