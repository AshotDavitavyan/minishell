/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:32:19 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/27 16:49:34 by vgribkov         ###   ########.fr       */
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
