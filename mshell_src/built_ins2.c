/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:04:59 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/19 14:01:50 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_exit(t_token *token)
{
	char **arr;

	arr = token -> token;
	if (ft_strlen_2d_arr(arr) == 1)
		exit(0);
	else if (ft_strlen_2d_arr(arr) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (ft_is_num(arr[1]) && long_long_check(arr[1]))
		exit(ft_atoi(arr[1]));
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arr[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

int	unset_acheck(t_shell *shell, char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (-1);
	while (shell -> envex[i])
	{
		if (ft_strncmp(shell -> envex[i], str, ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}
void	unset_delete(t_shell *shell, char *str)
{
	char **new_arr;
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (shell -> envex[i])
		i++;
	new_arr = malloc(sizeof(char *) * i);
	i = 0;
	while(shell -> envex[j])
	{
		if (ft_strncmp(shell -> envex[j], str, ft_strlen(str)) != 0)
			new_arr[i] = shell -> envex[j];
		if (ft_strncmp(shell -> envex[j], str, ft_strlen(str)) != 0)
			i++;
		j++;
	}
	new_arr[i] = NULL;
	shell -> envex = new_arr;
}

int	bi_unset(t_shell *shell)
{
	int	i;
	char **arr;

	arr = shell -> token -> token;
	i = 0;
	while (arr[++i])
	{
		if (unset_acheck(shell, arr[i]) == 1)
			unset_delete(shell, arr[i]);
		else if (unset_acheck(shell, arr[i]) == -1)
			return (1);
	}
	return (0);
}
