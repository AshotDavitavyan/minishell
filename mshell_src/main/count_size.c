/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:01:18 by adavitav          #+#    #+#             */
/*   Updated: 2023/07/27 15:03:25 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_quotes(char *u, int *p, int size)
{
	char	type;

	type = u[(*p)++];
	while (u[*p] != type && u[*p] != '\0')
	{
		size++;
		(*p)++;
	}
	if (u[(*p)++] == '\0')
	{
		printf("%s\n", "minishell: Syntax error detected");
		g_global_error = 258;
		return (-1);
	}
	return (size);
}

int	handle_redirs(char *user_input, int pos)
{
	char	type;

	type = user_input[pos];
	if (user_input[pos + 1] == type)
		return (4);
	else if (user_input[pos] == '|' || user_input[pos + 1] != type)
		return (3);
	return (96);
}

char	*put_spaces(char *user_input, int i, int size)
{
	int		j;
	char	*input_new;

	while (user_input[i])
	{
		if (user_input[i] == 34 || user_input[i] == 39)
		{
			j = skip_quotes(user_input, &i, 2);
			if (j == -1)
				return (NULL);
			size += j;
			continue ;
		}
		if (user_input[i] == '<' || user_input[i] == '>'
			|| user_input[i] == '|')
		{
			size += handle_redirs(user_input, i);
			i += (handle_redirs(user_input, i) - 2);
			continue ;
		}
		size++;
		i++;
	}
	input_new = (char *)malloc((size + 2) * sizeof(char));
	return (alloc(user_input, input_new));
}
