#include "minishell.h"

void	heredoc(t_token_small **tokens, t_token **token_final)
{
	(*token_final)->here_doc_flag = 1;
	*tokens = (*tokens)->next;
	(*token_final)->sep_arr = add_fd((*token_final)->sep_arr, *tokens, 0, NULL);
}

void	pick_the_right_flag(t_token **tokfin, t_token_small **tokens)
{
	while (*tokens != NULL)
	{
		if (check_for_special_signs(*tokens) == 3)
		{
			(*tokfin)->redir_flag_outout = 0;
			(*tokfin)->redir_flag_out = 1;
		}
		else if (check_for_special_signs(*tokens) == 4)
		{
			(*tokfin)->redir_flag_outout = 1;
			(*tokfin)->redir_flag_out = 0;
		}
		else if (check_for_special_signs(*tokens) == 5)
		{
			(*tokens) = (*tokens)->next;
			return ;
		}
		(*tokens) = (*tokens)->next;
	}
}

void	check_tokfin(t_token **tokfin, t_token_small *tokens)
{
	while (*tokfin)
	{
		if ((*tokfin)->redir_flag_outout == 1 && (*tokfin)->redir_flag_out == 1)
			pick_the_right_flag(tokfin, &tokens);
		*tokfin = (*tokfin)->next;
	}
}

void	add_funct_name(t_token **tokfin, t_token_small **tokens)
{
	(*tokfin)->token = add_fd((*tokfin)->token, *tokens, 0, NULL);
}

void	parse_tokens(t_token_small *tokens, t_token **token_final, t_token_small *head)
{
	token_final = tokenfinaladd(token_final, tokens);
	t_token *token_save = *token_final;
	while (tokens != NULL)
	{
		if (check_for_special_signs(tokens) == 1 || check_for_special_signs\
		(tokens) == 3 || check_for_special_signs(tokens) == 4)
		{
			add_redirs(&tokens, token_final);
			continue ;
		}
		else if (check_for_special_signs(tokens) == 5)
		{
			token_final = tokenfinaladd(token_final, tokens);
			*token_final = (*token_final)->next;
		}
		else if (check_for_special_signs(tokens) == 2)
			heredoc(&tokens, token_final);
		else
			add_funct_name(token_final, &tokens);
		tokens = tokens -> next;
	}
	tokens = head;
	check_tokfin(token_final, tokens);
	*token_final = token_save;
}
