/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_usr_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:29:35 by adavitav          #+#    #+#             */
/*   Updated: 2023/07/27 18:29:37 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*space_skip(char *user_input)
{
	while (*user_input == ' ' && *user_input)
		user_input++;
	return (user_input);
}

void	alloc_quotes(char **user_input, char **input_new)
{
	char	type;

	type = *(*user_input)++;
	*(*input_new)++ = type;
	while (**user_input != type)
	{
		**input_new = **user_input;
		(*input_new)++;
		(*user_input)++;
	}
	*(*input_new)++ = *(*user_input)++;
}

void	alloc_redpip(char **user_input, char **input_new)
{
	char	type;

	type = *(*user_input)++;
	if (**user_input != type || *(*user_input - 1) == '|')
	{
		*(*input_new)++ = ' ';
		*(*input_new)++ = type;
		*(*input_new)++ = ' ';
	}
	else
	{
		*(*input_new)++ = ' ';
		*(*input_new)++ = type;
		*(*input_new)++ = type;
		*(*input_new)++ = ' ';
		(*user_input)++;
	}
}

char	*alloc(char *u_i, char *input_new)
{
	char	*start;

	start = input_new;
	while (*u_i)
	{
		if (*u_i == 34 || *u_i == 39)
		{
			alloc_quotes(&u_i, &input_new);
			continue ;
		}
		if (*u_i == '|' || *u_i == '<' || *u_i == '>')
		{
			alloc_redpip(&u_i, &input_new);
			continue ;
		}
		*(input_new++) = *(u_i++);
	}
	*(input_new++) = ' ';
	*input_new = '\0';
	input_new = start;
	return (input_new);
}
