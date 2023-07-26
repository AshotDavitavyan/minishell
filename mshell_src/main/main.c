#include "../../includes/minishell.h"

//leaks, buffer overflows

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

int	lexing(char *u_i, t_token_small **tokens, t_shell **shell, t_token **tbig)
{
	char *u_i_space;

	u_i_space = put_spaces(u_i);
	free(u_i);
	if (u_i_space == NULL)
		return (-1);
	get_tokens(u_i_space, tokens, 0);
	free(u_i_space);
	init_shell(tokens, shell);
	handle_dollar_signs(tokens);
	if ((*tokens) == NULL)
		return (-1);
	if (parse_tokens(*tokens, tbig, *tokens) == (-1))
		return (-1);
	return (0);
}

void	sighandler(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	global_error = 1;
	(void)signum;
}

void	shell_token(t_token *token_final, t_shell *shell)
{
	if (token_final)
	shell->token = token_final;
	while (token_final)
	{
		token_final->shell = shell;
		token_final = token_final->next;
	}
}

int	global_error = 0;

int	main(int argc, char **argv, char **env)
{
	t_token_small *tokens;
	t_token *token_final;
	t_shell *shell;
	char *user_input;

	tokens = NULL;
	token_final = NULL;
	(void)argv;
	(void)argc;
	shell = malloc(sizeof(t_shell));
	init_env(&shell, env);
	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sighandler);
		user_input = readline("\033[94mminishell$\033[0m ");
		if (user_input == NULL)
			exit(global_error);
		if (!user_input || *user_input == '\0')
			continue ;
		add_history(user_input);
		if (lexing(user_input, &tokens, &shell, &token_final) != (-1))
		{
			shell_token(token_final, shell);
			if ((tokens) == NULL)
				continue ;
			exec(shell);
		}
		free_tokens(&tokens);
		free_big_tokens(&token_final);
		system("leaks minishell");
	}
	return (0);
}
