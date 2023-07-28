/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:29:58 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/27 18:04:32 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_strcmp(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (-1);
	while (*str1 && *str1 - *str2 == 0)
	{
		str1++;
		str2++;
	}
	return ((unsigned char)*str1 - (unsigned char)*str2);
}

char	*str_to_lower(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
	return (str);
}

int	bi_avail(t_token *token)
{
	char	**arr;

	arr = token -> token;
	if (!arr)
		return (0);
	if (ft_strcmp("env", str_to_lower(arr[0])) == 0
		|| ft_strcmp("pwd", str_to_lower(arr[0])) == 0
		|| ft_strcmp("echo", str_to_lower(arr[0])) == 0
		|| ft_strcmp("exit", str_to_lower(arr[0])) == 0
		|| ft_strcmp("export", str_to_lower(arr[0])) == 0
		|| ft_strcmp("unset", str_to_lower(arr[0])) == 0
		|| ft_strcmp("env", str_to_lower(arr[0])) == 0
		|| ft_strcmp("pwd", str_to_lower(arr[0])) == 0
		|| ft_strcmp("echo", str_to_lower(arr[0])) == 0
		|| ft_strcmp("cd", arr[0]) == 0
		|| ft_strcmp("exit ", str_to_lower(arr[0])) == 0
		|| ft_strcmp("export", str_to_lower(arr[0])) == 0
		|| ft_strcmp("unset", str_to_lower(arr[0])) == 0
	)
	{
		return (1);
	}
	return (0);
}
