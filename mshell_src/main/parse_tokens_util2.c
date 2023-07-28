/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_util2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:57:35 by adavitav          #+#    #+#             */
/*   Updated: 2023/07/28 13:57:36 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_small	*reset_tokens(t_token **token_final, \
t_token *token_save, t_token_small *head)
{
	*token_final = token_save;
	return (head);
}

void	parse_tokens_util1(t_token **token_final, t_token_small *tokens)
{
	token_final = tokenfinaladd(token_final, tokens);
	*token_final = (*token_final)->next;
}

t_token	*parse_tokens_util2(t_token **token_final, t_token_small *tokens)
{
	token_final = tokenfinaladd(token_final, tokens);
	return (*token_final);
}

int	find_err(t_token *tokfin)
{
	while (tokfin != NULL)
	{
		if (tokfin->err == 258)
			return (1);
		tokfin = tokfin->next;
	}
	return (0);
}
