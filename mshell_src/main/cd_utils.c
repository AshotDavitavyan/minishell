/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:33:53 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/26 16:07:31 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_old_pwd(t_shell *shell)
{
	int		i;
	char	cwd[PATH_MAX];
	char	*oldpwd;
	char	*pwd;

	i = 0;
	pwd = getcwd(cwd, sizeof(cwd));
	oldpwd = ft_strdup("OLDPWD=");
	oldpwd = ft_strjoin(oldpwd, pwd);
	while (shell -> envex[i])
	{
		if (ft_strncmp(shell -> envex[i], "OLDPWD", 6) == 0)
		{
				free(shell -> envex[i]);
			shell -> envex[i] = oldpwd;
			break ;
		}
		i++;
	}
}

void	change_new_pwd(t_shell *shell)
{
	int		i;
	char	cwd[PATH_MAX];
	char	*oldpwd;
	char	*pwd;

	i = 0;
	pwd = getcwd(cwd, sizeof(cwd));
	oldpwd = ft_strdup("PWD=");
	oldpwd = ft_strjoin(oldpwd, pwd);
	while (shell -> envex[i])
	{
		if (ft_strncmp(shell -> envex[i], "PWD", 6))
		{
			free(shell -> envex[i]);
			shell -> envex[i] = oldpwd;
			break ;
		}
		i++;
	}
}
