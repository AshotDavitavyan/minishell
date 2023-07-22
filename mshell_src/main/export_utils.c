/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:50:06 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/21 15:19:11 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	push_in_arr(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	**new_arr;

	i = 0;
	while (shell -> envex[i])
		i++;
	new_arr = (char **)malloc(sizeof(char *) * (i + 2));
	j = 0;
	while (j < i)
	{
		new_arr[j] = shell -> envex[j];
		j++;
	}
	new_arr[j] = ft_strdup(str);
	new_arr[++j] = NULL;
	free(shell -> envex);
	shell -> envex = new_arr;
	return (0);
}

int	find_dup(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	*temp;

	temp = ft_strdup(str);
	i = 0;
	j = 0;
	while (temp[j])
	{
		if (temp[j] == '=' || temp[j] == '+')
		{
			temp[j] = '\0';
			break ;
		}
		j++;
	}
	while (shell -> envex[i])
	{
		if (ft_strncmp(shell -> envex[i], str, ft_strlen(temp)) == 0)
			return (i);
		i++;
	}
	free(temp);
	return (-1);
}

char	*strdup_bez_pls(char *arr)
{
	int		i;
	int		j;
	char	*new_arr;

	i = -1;
	j = 0;
	while (arr[++i])
		;
	new_arr = (char *)malloc(sizeof(char ) * i);
	while (*arr)
	{
		if (*arr == '+')
			arr++;
		new_arr[j] = *arr;
		j++;
		arr++;
	}
	new_arr[j] = '\0';
	return (new_arr);
}

int	bi_export2(t_shell *shell, char **arr)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (arr[++j])
	{
		if ((i = find_dup(shell, arr[j])) != -1)
		{
			if (ft_strchr(arr[j], '+'))
				shell -> envex[i] = ft_strjoin(shell -> envex[i], ft_strchr(arr[j], '+') + 2);
			else
			{
				free(shell -> envex[i]);
				shell -> envex[i] = NULL;
				shell -> envex[i] = arr[j];
			}
			return (0);
		}
		if (ft_strchr(arr[j], '+'))
			arr[j] = strdup_bez_pls(arr[j]);
		return (push_in_arr(shell, arr[j]));
	}
	return (1);
}
