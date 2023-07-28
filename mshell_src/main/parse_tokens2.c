/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:56:55 by adavitav          #+#    #+#             */
/*   Updated: 2023/07/28 13:56:56 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_special_signs(t_token_small *tokens)
{
	if (ft_strnstr(tokens->name, "<", 1)
		&& ft_strlen(tokens->name) == 1 && tokens->var_flag == 0)
		return (1);
	else if (ft_strnstr(tokens->name, "<<", 2)
		&& ft_strlen(tokens->name) == 2 && tokens->var_flag == 0)
		return (2);
	else if (ft_strnstr(tokens->name, ">", 1)
		&& ft_strlen(tokens->name) == 1 && tokens->var_flag == 0)
		return (3);
	else if (ft_strnstr(tokens->name, ">>", 2)
		&& ft_strlen(tokens->name) == 2 && tokens->var_flag == 0)
		return (4);
	else if (ft_strnstr(tokens->name, "|", 1)
		&& ft_strlen(tokens->name) == 1 && tokens->var_flag == 0)
		return (5);
	return (0);
}

char	**add_fd(char **current, t_token_small *tokens, \
int size, char **to_return)
{
	char	**ptr;

	ptr = current;
	if (tokens == NULL)
	{
		printf("Here\n");
		return (hand_s("syntax error near unexpected token", "newline"));
	}
	if (check_for_special_signs(tokens) != 0 && tokens->type == 0)
	{
		printf("HEHE\n");
		return (hand_s("syntax error near unexpected token", tokens->name));
	}
	if (current == NULL)
	{
		to_return = (char **)malloc((2) * sizeof(char *));
		to_return[0] = ft_strdup(tokens->name);
		to_return[1] = NULL;
	}
	else
	{
		while (*ptr)
		{
			ptr++;
			size++;
		}
		to_return = (char **)malloc((size + 2) * sizeof(char *));
		arrcpy(to_return, current, tokens->name);
		free_arr(current);
	}
	return (to_return);
}

int	add_redirs(t_token_small **tokens, t_token **tokfin)
{
	while (*tokens != NULL)
	{
		if (check_for_special_signs(*tokens) == 1)
		{
			check_spec_signs_one(tokfin, tokens);
			if ((*tokfin)->redir_fd_in == NULL)
				return (-1);
		}
		else if (check_for_special_signs(*tokens) == 3)
		{
			check_spec_signs_three(tokfin, tokens);
			if ((*tokfin)->redir_fd_out == NULL)
				return (-1);
		}
		else if (check_for_special_signs(*tokens) == 4)
		{
			check_spec_signs_four(tokfin, tokens);
			if ((*tokfin)->redir_fd_out == NULL)
				return (-1);
		}
		else
			return (0);
		(*tokens) = (*tokens)->next;
	}
	return (0);
}

t_token	**tokenfinaladd(t_token **str, t_token_small *tokens)
{
	t_token	*to_add;

	to_add = (t_token *)malloc(sizeof(t_token));
	to_add->here_fd = 0;
	to_add->here_doc_flag = 0;
	to_add->sep_arr = NULL;
	to_add->redir_flag_out = 0;
	to_add->redir_flag_in = 0;
	to_add->redir_flag_outout = 0;
	to_add->redir_fd_out = NULL;
	to_add->redir_fd_in = NULL;
	to_add->token = NULL;
	to_add->next = NULL;
	to_add->shell = tokens->shell;
	if (*str != NULL)
		(*str)->next = to_add;
	else
		(*str) = to_add;
	return (str);
}
