#include "minishell.h"

void	error(void)
{
	write(2, "Error\n", 6);
	exit (1);
}

char	*space_skip(char *user_input)
{
	while (*user_input == ' ')
		user_input++;
	return (user_input);
}

char	*add_quote_token(char *user_input, char type)
{
	int		i;
	char	*token;

	i = 1;
	user_input++;
	while (user_input[i] && user_input[i] != type)
		i++;
	if (user_input[i] != type)
		error();
	token = (char *)malloc((i + 1) * sizeof(char));
	i = 0;
	while (*user_input != type)
	{
		token[i++] = *user_input;
		user_input++;
	}
	token[i] = '\0';
	printf("quote_token:[%s]\n", token);
	return (++user_input);
}

//------------------Token Print here----------------//

int	flags_check(char *user_input)
{
		if (*user_input == ' ' && space_skip(user_input) == '-')
			return (1);
		// else if (*user_input == ' ' && ((space_skip(user_input) == 34) ||
		//  space_skip(user_input) == 39)) && *(space_skip(user_input) + 1) == '-')
		// 	return (2);
}

char	*add_flags(char *user_input)
{
	char	*flags;
	
	return (flags);
}

char	*add_token(char *user_input, int i)
{
	char	*token;
	char	*flags;

	flags = NULL;
	if (i == 1 && *user_input == '\0')
		return NULL;
	token = (char *)malloc((i + 1) * sizeof(char));
	while (i != 0)
	{
		user_input--;
		i--;
	}
	while (*user_input != ' ' && *user_input != '\0')
	{
		token[i++] = *user_input;
		user_input++;
	}
	user_input++;
	token[i] = '\0';
	if (flags_check(user_input) == 1)
		flags = add_flags(user_input)
	printf("non_quote_token:[%s]\n", token);
	create_token(token);
	return (user_input);
}

void	get_tokens(char *user_input, t_token *structure)
{
	(void)structure;
	int	i;

	i = 0;
	user_input = space_skip(user_input);
	while (*user_input)
	{
		if (*user_input == 34 || *user_input == 39)
		{
			user_input = add_quote_token(user_input, *user_input);
			i = 0;
			if (!(*user_input))
			{
				i = 1;
				break ;
			}
			continue ;
		}
		if (*user_input == ' ')
		{
			user_input = add_token(user_input, i);
			user_input = space_skip(user_input);
			i = 0;
			continue ;
		}
		user_input++;
		i++;
	}
	if (*user_input == '\0')
		add_token(user_input, i);
}

int	alloc_quotes(char *user_input, char *input_new, int pos_usr, int pos_new)
{
	char	type;
	int		old_pos;

	type = user_input[pos_usr++];
	input_new[pos_new++] = type;
	old_pos = pos_new;

	while (user_input[pos_usr] != type)
	{
		input_new[pos_new] = user_input[pos_usr];
		pos_new++;
		pos_usr++;
	}
	input_new[pos_new++] = type;
	return (pos_new - old_pos + 1);
}

int	alloc_redpip(char *user_input, char *input_new, int pos_usr, int pos_new)
{
	char	type;

	type = user_input[pos_usr++];
	if (user_input[pos_usr] != type)
	{
		input_new[pos_new++] = ' ';
		input_new[pos_new++] = type;
		input_new[pos_new++] = ' ';
		return (3);
	}
	else
	{
		input_new[pos_new++] = ' ';
		input_new[pos_new++] = type;
		input_new[pos_new++] = type;
		input_new[pos_new++] = ' ';
		return (4);
	}
}

static char	*alloc(char *u_i, char *input_new, int j, int i)
{
	int	add;

	add = 0;
	while (u_i[i])
	{
		if (u_i[i] == 34 || u_i[i] == 39)
		{
			add = alloc_quotes(u_i, input_new, i, j);
			i += add;
			j += add;
			continue ;
		}
		if (u_i[i] == '|' || u_i[i] == '<' || u_i[i] == '>')
		{
			add = alloc_redpip(u_i, input_new, i, j);
			i += add - 2;
			j += add;
			continue ;
		}
		input_new[j++] = u_i[i++];
	}
	input_new[j] = '\0';
	return (input_new);
}

int	skip_quotes(char *user_input, int pos)
{
	char	type;
	int		size;

	type = user_input[pos++];
	size = 2;
	while (user_input[pos] != type && user_input[pos] != '\0')
	{
		size++;
		pos++;
	}
	if (user_input[pos] == '\0')
		error();
	return (size);
}

int	handle_redirs(char *user_input, int pos)
{
	char	type;
	int		size;

	type = user_input[pos];
	size = 0;

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
			size += skip_quotes(user_input, i);
			i += skip_quotes(user_input, i);
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
	input_new = (char *)malloc((size + 1) * sizeof(char));
	return (alloc(user_input, input_new, 0, 0));
}

void	lexing(char *user_input, t_token *structure)
{
	user_input = put_spaces(user_input);
	get_tokens(user_input, structure);
}

int	main(int argc, char **argv, char **env)
{
	t_token structure;

	(void)argv;
	(void)argc;
	(void)env;
	char *user_input;

	while (1)
	{
		user_input = readline("minishell$ ");
		lexing(user_input, &structure);
	}
	return (0);
}
