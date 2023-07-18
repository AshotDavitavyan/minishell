#include "minishell.h"

//single pipe error
//echo $?
//check tokens if they're empty
//check big tokens if they're empty
//$"USER" prints adavitav, should print USER
//$$USER.1 malloc error 
//$USER1 malloc error prints davitav instead of adavitav or avitav if $USER12
//remove token if variable does not exist
//Signals
//Numbers with dollar signs
//Errors, parse errors etc
//leaks, buffer overflows
//create env variable which is special sign and execute with it
//add history


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

void	lexing(char *u_i, t_token_small **tokens, t_shell **shell, t_token **tbig)
{
	u_i = put_spaces(u_i);
	get_tokens(u_i, tokens, 0);
	init_shell(tokens, shell);
	handle_dollar_signs(tokens);
	parse_tokens(*tokens, tbig, *tokens);
	print_big_token(*tbig);
}

void	sighandler(int signum)
{
	printf("\n");
	rl_on_new_line();
//	rl_replace_line("", 0);
	rl_redisplay();
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
	global_error = 0;
	while (1)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, SIG_IGN);
		user_input = readline("shell$ ");
		add_history(user_input);
		lexing(user_input, &tokens, &shell, &token_final);
		shell_token(token_final, shell);
		exec(shell);
		free_tokens(&tokens);
		free_big_tokens(&token_final);
	}
	return (0);
}
