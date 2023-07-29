/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:56:44 by adavitav          #+#    #+#             */
/*   Updated: 2023/07/28 13:56:45 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_tokfin(t_token **tokfin, t_token_small *tokens, t_token *save)
{
	while (*tokfin)
	{
		if ((*tokfin)->redir_flag_outout == 1 && (*tokfin)->redir_flag_out == 1)
			pick_the_right_flag(tokfin, &tokens);
		*tokfin = (*tokfin)->next;
	}
	*tokfin = save;
	if (find_err(*tokfin) == 1)
		return (-1);
	while (tokens)
	{
		if (check_for_special_signs(tokens) == 5)
		{
			if (tokens->prev == NULL || tokens->next == NULL)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				g_global_error = 258;
				(*tokfin)->err = 258;
				return (-1);
			}
		}	
		tokens = tokens->next;
	}
	return (0);
}

t_token_small	*put_flag(t_token_small **tokens, t_token_small \
*head, int count, t_token **tokfin)
{
	t_token_small	*ptr;

	(*tokfin)->token = add_fd((*tokfin)->token, head, 0, NULL);
	if (*tokens == NULL && count > 0)
	{
		while (head->next != NULL)
		head = head->next;
		ptr = head;
		free(head->name);
		ptr->name = ft_strdup("-n");
	}
	else if (*tokens != NULL && count > 0)
	{
		*tokens = (*tokens)->prev;
		ptr = *tokens;
		free((*tokens)->name);
		ptr->name = ft_strdup("-n");
	}
	else
		ptr = head->next;
	return (ptr);
}

void	add_funct_name(t_token **tokfin, t_token_small \
**tokens, t_token_small *save, int count)
{
	int	i;

	if ((*tokens)->next != NULL && check_echo((*tokens)->name) \
	== 0 && (*tokens)->next->name[0] == '-'
		&& str_find((*tokfin)->token) != 1)
	{
		(*tokens) = (*tokens)->next;
		while (*tokens)
		{
			i = 1;
			while ((*tokens)->name[i] && (*tokens)->name[0] == '-'
				&& (*tokens)->name[i] == 'n')
				i++;
			if ((*tokens)->name[i - 1] == 'n' && (*tokens)->name[i] == '\0')
				count++;
			else
				break ;
			*tokens = (*tokens)->next;
		}
		(*tokens) = put_flag(tokens, save, count, tokfin);
	}
	(*tokfin)->token = add_fd((*tokfin)->token, *tokens, 0, NULL);
}

int	parse_tokens(t_token_small *tokens, t_token \
	**tokfin, t_token_small *head, t_token *token_save)
{
	token_save = parse_tokens_util2(tokfin, tokens);
	while (tokens != NULL)
	{
		if (check_for_special_signs(tokens) == 1 || check_for_special_signs \
		(tokens) == 3 || check_for_special_signs(tokens) == 4)
		{
			if (add_redirs(&tokens, tokfin) == -1)
				break ;
			continue ;
		}
		else if (check_for_special_signs(tokens) == 5)
			parse_tokens_util1(tokfin, tokens);
		else if (check_for_special_signs(tokens) == 2)
		{
			if (heredoc(&tokens, tokfin) == (-1))
				break ;
		}
		else
			add_funct_name(tokfin, &tokens, tokens, 0);
		tokens = tokens -> next;
	}
	tokens = reset_tokens(tokfin, token_save, head);
	if ((*tokfin)->err == 258 || check_tokfin(tokfin, tokens, *tokfin) == (-1))
		return (-1);
	return (0);
}
