/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:30:43 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/28 14:50:41 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bi_echo(t_token *token)
{
	char	**arr;
	int		flag;
	int		i;

	arr = token -> token;
	i = 0;
	if (ft_strcmp(arr[1], "-n") == 0)
		flag = 1;
	else
		flag = 0;
	if (flag)
		i++;
	while (arr[++i])
	{
		printf("%s", arr[i]);
		if (arr[i + 1])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}

void	fd_cd_print_status(char *cmd)
{
	if (cmd)
		;
	g_global_error = 1;
	if (errno == 13)
	{
		ft_putstr_fd("minishell : cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied \n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	g_global_error = 1;
}

void	error_no_dir(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_global_error = 1;
}

void	error_perm_denied(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("/: Permission denied\n", 2);
	g_global_error = 1;
}

int	bi_export2(t_shell *shell, char **arr, int i)
{
	int		j;
	char	*temp;

	j = 0;
	while (arr[++j])
	{
		if ((find_dup(shell, arr[j], 0)) != -1)
		{
			i = find_dup(shell, arr[j], 0);
			if (ft_strchr(arr[j], '+'))
			{
				if (!ft_strchr(shell -> envex[i], '='))
					shell -> envex[i] = ft_strjoin(shell -> envex[i], "=");
				temp = ft_strchr(arr[j], '+') + 2;
				shell -> envex[i] = ft_strjoin(shell -> envex[i], temp);
			}
			else
				help_exp(&shell, i, arr[j]);
		}
		else if (ft_strchr(arr[j], '+'))
			arr[j] = strdup_bez_pls(arr[j]);
		else
			push_in_arr(shell, arr[j]);
	}
	return (0);
}
