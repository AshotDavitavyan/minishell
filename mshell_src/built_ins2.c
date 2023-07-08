/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:04:59 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/08 19:15:48 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_exit(t_token *token)
{
	char **arr;

	arr = ft_split(token -> token, ' ');
	if (ft_strlen_2d_arr(arr) == 1)
		exit(0);
	else if (ft_strlen_2d_arr(arr) > 2)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else if (ft_is_num(arr[1]) && long_long_check(arr[1]))
		exit(ft_atoi(arr[1]));
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arr[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	unset_acheck(t_shell *shell, char *str)
{
	int i;

	i = 0;
	while (shell -> envex[i])
	{
		if (ft_strncmp(shell -> envex[i], str, ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return 0;
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

void	bi_unset(t_shell *shell)
{
	t_token *tok;
	tok = shell -> token -> next;
	int	i;
	char **arr = ft_split(shell -> token -> token, ' ');

	i = 0;
	while (arr[++i])
	{
		if (unset_acheck(shell, arr[i]) == 1)
			unset_delete(shell, arr[i]);
	}
}

int	bi_avail(t_shell *shell)
{
	if (ft_strncmp("env", shell -> token -> token, 3) == 0 ||
		ft_strncmp("pwd", shell -> token -> token, 3) == 0 ||
		ft_strncmp("echo", shell -> token -> token, 4) == 0 ||
		ft_strncmp("cd", shell -> token -> token, 2) == 0 ||
		ft_strncmp("exit", shell -> token -> token, 4) == 0 ||
		ft_strncmp("export", shell -> token -> token, 6) == 0 ||
		ft_strncmp("unset", shell -> token -> token, 5) == 0 ||
		ft_strncmp("env ", shell -> token -> token, 4) == 0 ||
		ft_strncmp("pwd ", shell -> token -> token, 4) == 0 ||
		ft_strncmp("echo ", shell -> token -> token, 5) == 0 ||
		ft_strncmp("cd ", shell -> token -> token, 3) == 0 ||
		ft_strncmp("exit ", shell -> token -> token, 5) == 0 ||
		ft_strncmp("export ", shell -> token -> token, 7) == 0 ||
		ft_strncmp("unset ", shell -> token -> token, 6) == 0
		)
		{
			return (1);
		}
		return (0);
}