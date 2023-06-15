#include "minishell.h"

////////////////////////////QUOTE AFTER QUOTE WITHOUT SPACE/////////////////////////////
//Handle Dollar signs aswell
//Single characters disappear

void	error(void)
{
	write(2, "Error\n", 6);
	exit (1);
}

char	*space_skip(char *user_input)
{
	while (*user_input == ' ' && *user_input)
		user_input++;
	return (user_input);
}

//------------------Token Print here----------------//

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
	token[i] = '\0';
	printf("non_quote_token:[%s]\n", token);
	user_input++;
	// create_token(token, flags);
	return (user_input);
}

void	get_tokens(char *user_input, t_token *structure, int i)
{
	(void)structure;

	user_input = space_skip(user_input);
	while (*user_input)
	{
		if (*user_input == 34 || *user_input == 39)
		{
			user_input = add_quote_token(user_input, *user_input);
			i = (!(*user_input));
			if (!(*user_input))
				break ;
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

///////////////////////////////////////////////////////////////////////////////////


void	join_quote(char **user_input, char **input_new)
{
	char	type;

	type = *(*user_input)++;
	while (**user_input != type)
		*(*input_new)++ = *(*user_input)++;
	(*user_input)++;
}

int check(char *user_input, int step, int to_do, int *flag)
{
	int type;

	type = *user_input;
	if (to_do == 1 && step > 0 && *(user_input - 1) != ' ')
		return (1);
	if (to_do == 2)
	{
		if (*flag == 0)
		{
			user_input++;
			while (*user_input != type)
				user_input++;
		}
		if (*(user_input + 1) != ' ' && *(user_input + 1) != '|'
			&& *(user_input + 1) != '>' && *(user_input + 1) != '<' 
				&& *(user_input + 1) != '\0')
			return (1);
	}
	return (0);
}

void	alloc_quotes(char **user_input, char **input_new, int step, int flag)
{
	char	type;

	if (check(*user_input, step, 1, &flag) == 1)
	{
		join_quote(user_input, input_new);
		flag = 1;
	}
	if (check(*user_input, step, 2, &flag) == 1)
	{
		if (flag == 0)
			join_quote(user_input, input_new);
		return ;
	}
	if (flag == 1)
		return ;
	type = *(*user_input)++;
	*(*input_new)++ = type;
	while (**user_input != type)
	{
		**input_new = **user_input;
		(*input_new)++;
		(*user_input)++;
	}
	*(*input_new)++ = *(*user_input)++;
}

void	alloc_redpip(char **user_input, char **input_new)
{
	char	type;

	type = *(*user_input)++;
	if (**user_input != type || *(*user_input - 1) == '|')
	{
		*(*input_new)++ = ' ';
		*(*input_new)++ = type;
		*(*input_new)++ = ' ';
	}
	else
	{
		*(*input_new)++ = ' ';
		*(*input_new)++ = type;
		*(*input_new)++ = type;
		*(*input_new)++ = ' ';
		(*user_input)++;
	}
}

static char	*alloc(char *u_i, char *input_new, int step)
{
	char *start;

	start = input_new;
	while (*u_i)
	{
		if (*u_i == 34 || *u_i == 39)
		{
			alloc_quotes(&u_i, &input_new, step, 0);
			continue ;
		}
		if (*u_i == '|' || *u_i == '<' || *u_i == '>')
		{
			alloc_redpip(&u_i, &input_new);
			step = 0;
			continue ;
		}
		*(input_new++) = *(u_i++);
		step++;
	}
	*input_new = '\0';
	input_new = start;
	return (input_new);
}

/////////////////////////////////////////////////////////////////////////////////////

int	thank_you_norminette(char *u, int p)
{
	if (p > 0 && (u[p - 1] != ' ' || u[p - 1]
		!= '|'|| u[p - 1] != '<' || u[p - 1] != '>'))
		return (0);
	return (1);
}

void	check_for_quotes_after(char *u, int *p, int *size, int *flag)
{
	char type;

	if (u[*p] != 34 && u[*p] != 39)
		return ;
	type = u[(*p)++];
	(*size) -= (*flag);
	(*flag) = 0;
	while (u[*p] != type && u[*p] != '\0')
	{
		(*p)++;
		(*size)++;
		if (u[*p] == type && (u[*p + 1] == 34 || u[*p + 1] == 39))
			(*p) += 2;
	}
	if (u[*p] == '\0')
		error();
	(*p)++;
}

int	skip_quotes(char *u, int *p, int flag, int size)
{
	char	type;

	size = 2 *(thank_you_norminette(u, *p) == 1);
	flag = 2 *(thank_you_norminette(u, *p) == 1);
	type = u[(*p)++];
	while (u[*p] != type && u[*p] != '\0')
	{
		size++;
		(*p)++;
	}
	if (u[(*p)++] == '\0')
		error();
	check_for_quotes_after(u, p, &size, &flag);
	if (u[*p] != '\0' && u[*p] != ' ' && u[*p] != '|' && u[*p]
		!= '<' && u[(*p)] != '>' && u[*p] != 34 && u[*p] != 39)
	{
		while (u[*p] !=  ' ' && u[*p] != '\0' && u[*p] != '|' 
			&& u[*p] != '<' && u[*p] != '>' && u[*p] != 34 && u[*p] != 39)
		{
			size++;
			(*p)++;
		}
		size -= flag;
	}
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
			size += skip_quotes(user_input, &i, 2, 2);
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
	printf("%d\n", size);
	return (alloc(user_input, input_new, 0));
}

//////////////////////////////////////////////////////////////////////////////////////////

void	lexing(char *user_input, t_token *structure)
{
	user_input = put_spaces(user_input);
	get_tokens(user_input, structure, 0);
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
