/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:29:58 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/13 15:13:56 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **arr)
{
	int	i = 0;
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

int	bi_avail(t_token *token)
{
	char **arr;
	
	arr = ft_split(token -> token, ' ');
	if (ft_strcmp("env", arr[0]) == 0 ||
		ft_strcmp("pwd", arr[0]) == 0 ||
		ft_strcmp("echo", arr[0]) == 0 ||
		ft_strcmp("cd", arr[0]) == 0 ||
		ft_strcmp("exit", arr[0]) == 0 ||
		ft_strcmp("export", arr[0]) == 0 ||
		ft_strcmp("unset", arr[0]) == 0 ||
		ft_strcmp("env ", arr[0]) == 0 ||
		ft_strcmp("pwd ", arr[0]) == 0 ||
		ft_strcmp("echo ", arr[0]) == 0 ||
		ft_strcmp("cd ", arr[0]) == 0 ||
		ft_strcmp("exit ", arr[0]) == 0 ||
		ft_strcmp("export ", arr[0]) == 0 ||
		ft_strcmp("unset ", arr[0]) == 0
		)
		{
			ft_free(arr);
			return (1);
		}
		ft_free(arr);
		return (0);
}