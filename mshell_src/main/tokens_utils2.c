#include "../../includes/minishell.h"

int	check(char *user_input, char type, int i, int todo)
{
	if (todo == 1 && i > 0 && *(user_input - 1) != ' ')
		return (1);
	else if (todo == 2)
	{
		while (*user_input != type && *user_input != '\0')
			user_input++;
		if (*(user_input + 1) != ' ' && *(user_input + 1) != '\0')
			return (1);
	}
	else if (todo == 3)
	{
		if (*(user_input) != ' ' && *(user_input) != '\0')
			return (1);
	}
	return (0);
}

void	before_quote(char *user_input, int pos, char **token)
{
	int i;

	i = pos;
	while (pos > 0)
	{
		(*token)[pos-1] = *user_input;
		pos--;
		if(pos == 0)
			break ;
		user_input--;
	}
	(*token) += i;
}

int	after_quotes(char *user_input, char type)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (user_input[i] != type)
		i++;
	i++;
	while (user_input[i] != ' ' && user_input[i] != '\0')
	{
		if (user_input[i] == 34 || user_input[i] == 39)
		{
			type = user_input[i++];
			while (user_input[i++] != type)
				size++;
			continue ;
		}
		i++;
		size++;
	}
	return (size);
}
