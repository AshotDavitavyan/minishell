/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:54:39 by adavitav          #+#    #+#             */
/*   Updated: 2023/07/28 15:07:12 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lexing(char *u_i, t_token_small **tokens, t_shell **shell, t_token **tbig)
{
	char	*u_i_space;

	u_i_space = put_spaces(u_i, 0, 0);
	free(u_i);
	if (u_i_space == NULL)
		return (-1);
	get_tokens(u_i_space, tokens, 0);
	free(u_i_space);
	init_shell(tokens, shell);
	handle_dollar_signs(tokens);
	if ((*tokens) == NULL)
		return (-1);
	if (parse_tokens(*tokens, tbig, *tokens, NULL) == (-1))
		return (-1);
	return (0);
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

int	g_global_error = 0;

void	main_loop(t_token *token_final, t_token_small *tokens, \
t_shell **shell, char *user_input)
{
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sighandler);
		user_input = readline("\033[94mminishell$\033[0m ");
		if (user_input == NULL)
			exit(g_global_error);
		if (!user_input || *user_input == '\0')
		{
			free(user_input);
			continue ;
		}
		add_history(user_input);
		if (lexing(user_input, &tokens, shell, &token_final) != (-1))
		{
			shell_token(token_final, *shell);
			if ((tokens) == NULL)
				continue ;
			exec(*shell);
		}
		free_tokens(&tokens);
		free_big_tokens(&token_final);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_token_small	*tokens;
	t_token			*token_final;
	t_shell			*shell;

	tokens = NULL;
	token_final = NULL;
	shell = malloc(sizeof(t_shell));
	(void)argv;
	(void)argc;
	init_env(&shell, env);
	rl_catch_signals = 0;
	main_loop(token_final, tokens, &shell, NULL);
	return (0);
}
