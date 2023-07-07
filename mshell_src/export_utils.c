/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:50:06 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/07 21:15:36 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_in_arr(t_shell *shell, char *str)
{
	int i;
	int j;

	i = 0;
	while (shell -> envex[i])
		i++;
	char **new_arr = (char **)malloc(sizeof(char *) * (i + 2));
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
}

int	find_dup(t_shell *shell, char *str)
{
	int 	i;
	int		j;
	char	*temp;
	
	temp = ft_strdup(str);
	i = 0;
	j = 0;
	while(temp[j])
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

void	bi_export2(t_shell *shell, char **arr)//arr = export a b
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
			{
				shell -> envex[i] = ft_strjoin(shell -> envex[i], ft_strchr(arr[j], '+') + 2);
			}
			else
			{
				free(shell -> envex[i]);
				shell -> envex[i] = NULL;
				shell -> envex[i] = arr[j];
			}
			return ;
		}
		if (ft_strchr(arr[j], '+'))
			arr[j] = bez_plus(arr[j]);
		push_in_arr(shell, arr[j]);
	}
}