#include "minishell.h"

int	skip_quotes(char *u, int *p, int size)
{
	char	type;

	type = u[(*p)++];
	while (u[*p] != type && u[*p] != '\0')
	{
		size++;
		(*p)++;
	}
	if (u[(*p)++] == '\0')
		error();
	return (size);
}

int	handle_redirs(char *user_input, int pos)
{
	char	type;

	type = user_input[pos];
	if (user_input[pos + 1] == type)
		return (4);
	else if (user_input[pos] == '|' || user_input[pos + 1] != type)
		return (3);
	return (96);
}

char	*put_spaces(char *user_input)
{
	int		i;
	int		size;
	char	*input_new;

	i = 0;
	size = 0;
	while (user_input[i])
	{
		if (user_input[i] == 34 || user_input[i] == 39)
		{
			size += skip_quotes(user_input, &i, 2);
			continue ;
		}
		if (user_input[i] == '<' || user_input[i] == '>' || user_input[i] == '|')
		{
			size += handle_redirs(user_input, i);
			i += (handle_redirs(user_input, i) - 2);
			continue ;
		}
		size++;
		i++;
	}
	input_new = (char *)malloc((size + 2) * sizeof(char));
	return (alloc(user_input, input_new));
}