#include "minishell.h"

//should i strtrim variables?
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
	(void)shell;
	u_i = put_spaces(u_i);
	get_tokens(u_i, tokens, 0);
	// print_tokens(*tokens);
	init_shell(tokens, shell);
//	handle_dollar_signs(tokens);
	parse_tokens(*tokens, tbig, *tokens);
	

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

void	init_shell(t_token_small **tokens, t_shell **shell)
{
	t_token_small *ptr;
	(*shell)->token_small = *tokens;
	ptr = *tokens;
	while (ptr != NULL)
	{
		ptr->shell = *shell;
		ptr = ptr->next;
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
		if (!user_input || *user_input == '\0')
			continue ;
		add_history(user_input);
		lexing(user_input, &tokens, &shell, &token_final);
		shell_token(token_final, shell);
		//print_big_token(token_final);
		exec(shell);
		free_tokens(&tokens);
		free_big_tokens(&token_final);
	}
	return (0);
}
