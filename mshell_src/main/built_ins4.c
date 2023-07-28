/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:32:19 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/28 14:28:15 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bi_cd(t_token *token)
{
	char	**arr;
	DIR		*tmp;

	arr = token -> token;
	if (change_old_pwd(token -> shell, arr[1]) == 0)
		return (0);
	if (access(arr[1], F_OK))
	{
		error_no_dir(arr[1]);
		return (1);
	}
	tmp = opendir(arr[1]);
	if (!tmp)
		fd_cd_print_status(arr[1]);
	else
	{
		closedir(tmp);
		if (chdir(arr[1]) != 0)
		{
			error_perm_denied(arr[1]);
			return (1);
		}
		change_new_pwd(token -> shell);
	}
	return (0);
}

int	ft_strlen_2d_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}

void	free_ins(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

void	unset_delete(t_shell *shell, char *str)
{
	char	**new_arr;
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while (shell -> envex[i])
		i++;
	new_arr = malloc(sizeof(char *) * i);
	i = 0;
	while (shell -> envex[j])
	{
		if (ft_strncmp(shell -> envex[j], str, ft_strlen(str)))
		{
			new_arr[i] = ft_strdup(shell -> envex[j]);
			i++;
		}
		j++;
	}
	new_arr[i] = NULL;
	tmp = shell -> envex;
	shell -> envex = new_arr;
	ft_free(tmp);
}

int	bi_unset(t_shell *shell)
{
	int		i;
	char	**arr;

	arr = shell -> token -> token;
	i = 0;
	while (arr[++i])
	{
		if (unset_acheck(shell, arr[i]) == 1)
			unset_delete(shell, arr[i]);
		else
			return (1);
	}
	return (0);
}
