#include "minishell.h"

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

char	*replace_var(char *var_name, char **var_arr)
{
	char	*to_return;

	while (*var_arr)
	{
		if (ft_strncmp(*var_arr, var_name, ft_strchr_num(*var_arr, '=')) == 0)
			break ;
		var_arr++;
	}
	while (**var_arr != '=')
		*var_arr++;
	to_return = ft_strdup(ft_strtrim(*var_arr, '\''));
	free(var_name);
	return (to_return);
}

int	ft_strchr_num(const char *s, int c)
{
	char	loc;
	int		i;

	loc = (char)c;
	i = 0;
	while (*s != '\0')
	{
		if (*s == loc)
			return (i);
		s++;
		i++;
	}
	if (*s == loc)
		return (i);
	return (-1);
}

void	check_var(t_token **ptr, int dollar_index, int i)
{
	char	*new_name;
	char	*var_name;
	char	*sep;

	if (dollar_index == -1)
		return ;
	new_name = &(*ptr)->name[dollar_index + 1];
	sep = " <>|&./?@#$%^*-=+,[]{}\'\"";
	while (*new_name)
	{
		if (ft_strchr(sep, *new_name) != NULL)
			break ;
		new_name++;
		i++;
	}
	var_name = ft_substr((*ptr)->name, dollar_index, i + 1);
	if (squote_check()== 0)
		var_name = replace_var(var_name + 1, (*ptr)->shell->envex);
}

void	handle_dollar_signs(t_token **tokens)
{
	t_token *ptr;

	ptr = *tokens;
	while (ptr != NULL)
	{
		check_var(&ptr, ft_strchr_num((ptr)->name, '$'), 0);
		ptr = ptr->next;
	}
}

void	print_tokens(t_token *tokens)
{
	int i = 0;
	while (tokens != NULL)
	{
		printf("token:[%s]\n", tokens->name);
		tokens = tokens->next;
		i++;
	}
	printf("size:[%d]\n", i);
}

void	lexing(char *user_input, t_token **tokens)
{
	user_input = put_spaces(user_input);
	get_tokens(user_input, tokens, 0);
	print_tokens(*tokens);
	handle_dollar_signs(tokens);

}

void	init_env(t_shell **shell, char **envp)
{
	int	i = 0;
	while (envp[i])
		i++;
	(*shell) -> envex = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("OLDPWD", envp[i], 6) == 0)
			(*shell) -> envex[i] = ft_strdup("OLDPWD");
		else
			(*shell) -> envex[i] = ft_strdup(envp[i]);
	}
	(*shell) -> envex[i] = NULL;
}

void	init_shell(t_token **tokens, t_shell **shell)
{
	t_token *ptr;
	(*shell)->token = *tokens;
	ptr = *tokens;
	while (ptr != NULL)
	{
		ptr->shell = *shell;
		ptr = ptr->next;
	}
}

void	print_env(char **envp)
{
	while(*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_token *tokens;
	t_shell *shell;
	tokens = NULL;

	(void)argv;
	(void)argc;
	char *user_input;
	shell = malloc(sizeof(t_shell));
	init_env(&shell, env);
	while (1)
	{
		user_input = readline("shell$ ");
		lexing(user_input, &tokens);
		init_shell(&tokens, &shell);
		// print_env(tokens->shell->envex);
		free_tokens(&tokens);
	}
	return (0);
}
