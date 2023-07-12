#include "minishell.h"

char	*add_after_quotes(char **user_input, char *token, char type)
{
	while (**user_input != ' ' && **user_input != '\0')
	{
		if (**user_input == 34 || **user_input == 39)
		{
			type = *(*user_input)++;
			while (**user_input != type)
			{
				*token = **user_input;
				token++;
				(*user_input)++;
			}
			(*user_input)++;
			continue ;
		}
		*token = **user_input;
		token++;
		(*user_input)++;
	}
	return (token);
}

void	add_quote_token(char **user_input, char type, int pos, t_token **tokens)
{
	char	*token;
	char	*save;
	int		i;

	if (**user_input != 34 && **user_input != 39)
		return ;
	(*user_input)++;
	i = 0;
	while ((*user_input)[i] && (*user_input)[i] != type)
		i++;
	i += pos;
	if (check(*user_input, type, pos, 2) == 1)
		i += after_quotes(*user_input, type);
	token = (char *)malloc((i + 1) * sizeof(char));
	save = token;
	if (check(*user_input, type, pos, 1) == 1)
		before_quote(*(user_input) - 2, pos, &token);
	while (**user_input != type)
		*(token++) = *(*user_input)++;
	(*user_input)++;
	if (check(*user_input, type, pos, 3) == 1)
		token = add_after_quotes(user_input, (token), 97);
	*token = '\0';
	token = save;
	*tokens = create_token(*tokens, token, type);
}

void	add_token(char **user_input, int i, t_token **tokens)
{
	char	*token;
	int		s;

	s = i;
	if (i == 1 && **user_input == '\0')
		return ;
	token = (char *)malloc((i + 1) * sizeof(char));
	while (i != 0)
	{
		(*user_input)--;
		i--;
	}
	printf("%s\n", *user_input);
	while (i < s)
	{
		token[i++] = **user_input;
		(*user_input)++;
	}
	token[i] = '\0';
	(*user_input)++;
	*tokens = create_token(*tokens, token, 0);
}

int qch_usd(char *user_input, int i)
{
	while (i > 0)
	{
		if (*user_input == '$')
			return (1);
		user_input--;
		i--;
	}
	return (0);
}

int	qcheck(char **user_input, int *i, char type, int s)
{
	char *save;

	save = *user_input;
	type = *(*user_input)++;
	while (**user_input != type)
	{
		(*user_input)++;
		(*i)++;
	}
	(*user_input)++;
	if (**user_input != ' ' && **user_input != '\0')
	{
		while (**user_input != ' ' && **user_input != '\0')
		{
			(*user_input)++;
			(*i)++;
		}
		if (qch_usd(*user_input, (*i) + 2) == 1)
			return (1);
	}
	if (s > 0 && save[s - 1] != ' ' && qch_usd(*user_input, (*i) + 2) == 1)
		return (1);
	*user_input = save;
	*i = s;
	return (0);
}

void	get_tokens(char *user_input, t_token **tokens, int i)
{
	user_input = space_skip(user_input);
	while (*user_input)
	{
		if (*user_input == 34 || *user_input == 39)
		{
			if (qcheck(&user_input, &i, 0, i) == 1)
				add_token(&user_input, i + 2, tokens);
			add_quote_token(&user_input, *user_input, i, tokens);
			user_input = space_skip(user_input);
			i = (!(*user_input));
			if (!(*user_input))
				break ;
			continue ;
		}
		else if (*user_input == ' ')
		{
			add_token(&user_input, i, tokens);
			user_input = space_skip(user_input);
			i = (!(*user_input));
			continue ;
		}
		user_input++;
		i++;
	}
	add_token(&user_input, i, tokens);
}
