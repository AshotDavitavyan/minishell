/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_util3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:59:13 by adavitav          #+#    #+#             */
/*   Updated: 2023/07/28 13:59:14 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	arrcpy(char **to_be, char **current, char *to_add)
{
	int	i;

	i = 0;
	while (*current)
	{
		to_be[i] = ft_strdup(*current);
		i++;
		current++;
	}
	to_be[i++] = ft_strdup(to_add);
	to_be[i] = NULL;
}

char	**hand_s(char *to_print, char *token, char **to_free)
{
	printf("minishell: syntax error%s", to_print);
	printf(" `%s'\n", token);
	g_global_error = 258;
	free_arr(to_free);
	return (NULL);
}

void	check_spec_signs_one(t_token **tokfin, t_token_small **tokens)
{
	(*tokfin)->redir_flag_in = 1;
	*tokens = (*tokens)->next;
	(*tokfin)->redir_fd_in = add_fd((*tokfin)->redir_fd_in, *tokens, 0, NULL);
	if ((*tokfin)->redir_fd_in == NULL)
		(*tokfin)->err = 258;
}

void	check_spec_signs_three(t_token **tokfin, t_token_small **tokens)
{
	(*tokfin)->redir_flag_out = 1;
	*tokens = (*tokens)->next;
	(*tokfin)->redir_fd_out = add_fd((*tokfin)->redir_fd_out, *tokens, 0, NULL);
	if ((*tokfin)->redir_fd_out == NULL)
		(*tokfin)->err = 258;
}

void	check_spec_signs_four(t_token **tokfin, t_token_small **tokens)
{
	(*tokfin)->redir_flag_outout = 1;
	*tokens = (*tokens)->next;
	(*tokfin)->redir_fd_out = add_fd((*tokfin)->redir_fd_out, *tokens, 0, NULL);
	if ((*tokfin)->redir_fd_out == NULL)
		(*tokfin)->err = 258;
}
