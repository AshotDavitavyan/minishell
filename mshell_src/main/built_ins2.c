/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:04:59 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/28 14:57:19 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bi_exit(t_token *token)
{
	char	**arr;

	arr = token -> token;
	if (ft_strlen_2d_arr(arr) == 1)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else if (ft_strlen_2d_arr(arr) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_global_error = 1;
		return (1);
	}
	else if (ft_is_num(arr[1]) && long_long_check(arr[1]))
	{
		ft_putstr_fd("exit\n", 1);
		exit(ft_atoi(arr[1]));
	}
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arr[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

size_t	strlen_bef_eq(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
	}
	return (i);
}

char	*dup_bef_eq(char *str)
{
	char	*arr;
	int		i;

	i = -1;
	if (!str)
		return (NULL);
	arr = ft_strdup(str);
	while (arr[++i])
	{
		if (arr[i] == '=')
			break ;
	}
	arr[i] = '\0';
	return (arr);
}

int	unset_check(t_shell *shell, char *str, char *temp)
{
	int	i;

	i = 0;
	while (shell -> envex[i])
	{
		if (ft_strncmp(shell -> envex[i], str, ft_strlen(str)) == 0
			&& strlen_bef_eq(shell -> envex[i]) == ft_strlen(str))
		{
			free(temp);
			return (1);
		}
		i++;
	}
	free(temp);
	return (0);
}

int	unset_acheck(t_shell *shell, char *str)
{
	int		j;
	char	*del;
	char	*temp;

	del = "!()<>|&./?@#$%^*-=+,[]{}\'\"";
	j = 0;
	temp = dup_bef_eq(str);
	while (del[j])
	{
		if (ft_strchr(temp, del[j]) || ft_isdigit(str[0]) == 1)
		{
			ft_putstr_fd("minishell: \'", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			g_global_error = 1;
			free(temp);
			return (-1);
		}
		j++;
	}
	if (unset_check(shell, str, temp) == 1)
		return (1);
	return (0);
}
