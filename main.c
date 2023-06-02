#include "minishell.h"

void	error()
{
	write(2, "Error\n", 6);
	exit (1);
}

char	*get_quote_token(char *user_input, char type)
{
	int		i;
	char	*token;

	i = 1;
	user_input++;
	while (user_input[i] && user_input[i] != type)
		i++;
	if (user_input[i] != type)
		error();
	token = (char *)malloc(i * sizeof(char));
	i = 1;
	while (*user_input != type)
	{
		token[i++] = *user_input;
		user_input++;
	}
	user_input++;
	return (user_input);
}

char	*space_skip(char *user_input)
{
	while (*user_input == ' ')
		user_input++;
	return (user_input);
}

char	*add_token(char *user_input, int i)
{
	char	*token;

	token = (char *)malloc((i + 1) * sizeof(char));

	while (i != 0)
	{
		user_input--;
		i--;
	}
}

void	get_tokens(char *user_input)
{
	int	i;

	i = 0;
	while (*user_input)
	{
		if (*user_input == 34 || *user_input == 39)
		{
			user_input = get_quote_token(user_input, *user_input);
			i = 0;
		}
		if (*user_input == ' ')
		{
			user_input = add_token(user_input, i);
			i = 0;
		}

		user_input++;
	}
}

static char	*alloc(char *user_input, char *input_new, int j, int i)
{
	while (user_input[i])
	{
		if ((user_input[i] == '<' || user_input[i] == '>')
			&& user_input[i + 1] == user_input[i])
		{
			input_new[j++] = ' ';
			input_new[j++] = user_input[i++];
			input_new[j++] = user_input[i++];
			if (user_input[i])
				input_new[j++] = ' ';
			continue ;	
		}
		else if (user_input[i] == '|' || user_input[i] == '<'
			|| user_input[i] == '>')
		{
			input_new[j++] = ' ';
			input_new[j++] = user_input[i++];
			if (user_input[i])
				input_new[j++] = ' ';
			continue ;
		}
		input_new[j++] = user_input[i++];
	}
	return (input_new);
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
		if ((user_input[i] == '<' || user_input[i] == '>')
			&& user_input[i + 1] == user_input[i])
		{
			i++;
			size++;
		}
		else if (user_input[i] == '|' || user_input[i] == '<'
			|| user_input[i] == '>')
		{
			size++;
			size += (user_input[i + 1] != 0);
		}
		size++;
		i++;
	}
	input_new = (char *)malloc((size + 1) * (sizeof(char)));
	return (alloc(user_input, input_new, 0, 0));
}

void	lexing(char *user_input)
{
	user_input = put_spaces(user_input);
	get_tokens(user_input);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	char *user_input;

	while(*env)
	{
		printf("%s\n", *env);
		env++;
	}
	while (1)
	{
		user_input = readline("minishell$ ");
		lexing(user_input);
	}
	return (0);
}
