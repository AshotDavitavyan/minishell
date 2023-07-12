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
void	print_env(char **envp)
{
	while(*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
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

void	parse_tokens()

void	lexing(char *user_input, t_token **tokens, t_shell **shell)
{
	user_input = put_spaces(user_input);
	get_tokens(user_input, tokens, 0);
	init_shell(tokens, shell);
	// print_env((*tokens)->shell->envex);
	handle_dollar_signs(tokens);
	print_tokens(*tokens);
	parse_tokens(*tokens);
}

void	parse_tokens(t_token *tokens, t_token_big *token_final)
{
	while (tokens != NULL)
	{
		if (token -> name = )
		
		token = token -> next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_token *tokens;
	t_token_big *token_final;
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
		lexing(user_input, &tokens, &shell);
		// print_env(tokens->shell->envex);
		free_tokens(&tokens);
		//print_env(shell->envex);
	}
	return (0);
}
