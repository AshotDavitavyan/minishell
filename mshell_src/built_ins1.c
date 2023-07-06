/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:49:50 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/06 20:44:31 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_env(t_shell *shell)
{
	int i = 0;
	while (shell -> envex[i])
	{
		if (ft_strchr(shell -> envex[i], '='))
			printf("%s\n", shell -> envex[i]);
		i++;
	}
}

void	bi_export1(t_shell *shell)
{
	int	i;
	char **arr = ft_split_V(shell -> token -> token, ' ');
	i = 0;
	if (!arr[1])
	{
		while (shell -> envex[i])
		{
			def_putstr("declare -x ");
			def_putstr(shell -> envex[i]);
			printf("\n");
			i++;
		}
		return ;
	}
	bi_export2(shell, arr);
}

void	bi_pwd()
{
	char cwd[PATH_MAX];
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}

void	bi_echo(t_token *token)
{
	char **arr = ft_split_V(token -> token, ' ');
	int flag;
	int	i;

	i = 0;
	if (ft_strchr(arr[0], '-'))
		flag = 1;
	else
		flag = 0;
	while(arr[++i])
	{
		printf("%s", arr[i]);
		if (arr[i + 1])
			printf(" ");
	}
	if (!flag)
		printf("\n");
}

void	bi_cd(t_token *token)
{
	char **arr = ft_split_V(token -> token, ' ');
	change_old_pwd(token -> shell);
	if (chdir(arr[1]) != 0)
        printf("minishell: cd: %s: No such file or directory\n", token -> next -> token);
	change_new_pwd(token -> shell);
}
