/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:52:23 by adavitav          #+#    #+#             */
/*   Updated: 2023/07/28 13:52:23 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	single_dollar(char **name, char **new_name)
{
	char	*sep;

	sep = " <>|&./@#$%^*-=+,[]{}\'\"";
	if (ft_strchr(sep, (*name)[1]) != NULL || (*name)[1] == '\0')
	{
		if (new_name == NULL)
		{
			(*name)++;
			return (1);
		}
		else
		{
			**new_name = **name;
			(*new_name)++;
			(*name)++;
			return (1);
		}
	}
	return (0);
}

int	comp_vars(char **name, char **var_arr, int i, char *sep)
{
	int	j;

	if (single_dollar(name, NULL) == 1)
		return (1);
	if (isnum(name) == 1)
		return (0);
	if ((*name)[1] == '?')
	{
		(*name) += 2;
		return (intlen(g_global_error));
	}
	while (ft_strchr(sep, (*name)[i]) == NULL && (*name)[i] != '\0')
		i++;
	i--;
	while (*var_arr)
	{
		j = 0;
		while ((*var_arr)[j] != '=')
			j++;
		if (comp_vars_util(name, var_arr, i, j) == 1)
			return (env_len(*var_arr, name));
		var_arr++;
	}
	move_ptr(name);
	return (0);
}

int	quote_dollar(char **name, char **var_arr, int i, char type)
{
	if (type == 39)
	{
		while (**name != type && **name != '\0')
		{
			(*name)++;
			i++;
		}
		(*name)++;
		return (i);
	}
	while (**name != type)
	{
		if (**name == '$')
			i += comp_vars(name, var_arr, 1, " <>|&./?@#$%^*-=+,[]{}\'\"");
		if (**name != type)
		{
			(*name)++;
			i++;
		}
	}
	(*name)++;
	return (i);
}

void	check_var(t_token_small **ptr, int dollar_index, int i)
{
	char	*nam_ptr;
	char	*new_name;

	nam_ptr = (*ptr)->name;
	new_name = NULL;
	if (dollar_index == -1)
		return ;
	while (*nam_ptr)
	{
		if ((*nam_ptr == 34 || *nam_ptr == 39) && (*ptr)->type != 34)
		{
			i += quote_dollar(&nam_ptr, (*ptr)->shell->envex, 0, *(nam_ptr++));
			continue ;
		}
		if (*nam_ptr == '$')
		{
			i += comp_vars(&nam_ptr, (*ptr)->shell->envex, 1, \
			" <>|&./?@#$%^*-=+,[]{}\'\"");
			continue ;
		}
		nam_ptr++;
		i++;
	}
	new_name = (char *)ft_calloc((i + 1), 1);
	put_vars(new_name, ptr, (*ptr)->name, new_name);
}

void	handle_dollar_signs(t_token_small **tokens)
{
	t_token_small	*ptr;

	ptr = *tokens;
	while (ptr != NULL)
	{
		if (ptr->type != 39)
			check_var(&ptr, ft_strchr_num((ptr)->name, '$'), 0);
		if (ft_strlen(ptr->name) == 0)
		{
			ptr = tokendelone(ptr, tokens);
			continue ;
		}
		ptr = ptr->next;
	}
}
