/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:50:06 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/28 14:51:57 by vgribkov         ###   ########.fr       */
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
		new_arr[j] = ft_strdup(shell -> envex[j]);
		j++;
	}
	new_arr[j] = ft_strdup(str);
	new_arr[++j] = NULL;
	ft_free(shell -> envex);
	shell -> envex = new_arr;
	return (0);
}

int	find_dup(t_shell *shell, char *str, int i)
{
	int		j;
	char	*temp;

	temp = ft_strdup(str);
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
		{
			free(temp);
			return (i);
		}
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
	char	*temp;

	temp = arr;
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
	free(temp);
	return (new_arr);
}

char	*ft_strjoin_my(char const *s1, char const *s2)
{
	char	*arr;
	int		i;
	int		j;
	int		step;

	if (!s1 || !s2)
		return (NULL);
	step = 0;
	arr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	j = 0;
	if (!arr)
		return (NULL);
	while (s1[i])
		arr[step++] = s1[i++];
	while (s2[j])
		arr[step++] = s2[j++];
	arr[step] = '\0';
	free((char *)s2);
	return (arr);
}

void	help_exp(t_shell **shell, int i, char *arr)
{
	free((*shell)->envex[i]);
	(*shell)->envex[i] = NULL;
	(*shell)->envex[i] = ft_strdup(arr);
}
