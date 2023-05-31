#include "minishell.h"

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
