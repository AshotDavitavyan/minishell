/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:49:50 by vgribkov          #+#    #+#             */
/*   Updated: 2023/06/21 18:23:53 by vgribkov         ###   ########.fr       */
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

	i = 0;
	if (!shell -> token -> next)
	{
		while (shell -> envex[i])
		{
			printf("declare -x %s", shell -> envex[i]);
			if (shell->envex[i] && shell->envex[i][ft_strlen(shell->envex[i]) - 1] == '=')
				printf("\'\'");
			printf("\n");
			i++;
		}
		return ;
	}
	bi_export2(shell);
}

void	bi_pwd()
{
	char cwd[PATH_MAX];
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}

void	bi_echo(t_token *token)
{
	t_token *temp;
	
	temp = token;
	int flag;
	if (ft_strchr(token -> token, '-'))
		flag = 1;
	else
		flag = 0;
	temp = token -> next;
	while(temp)
	{
		printf("%s", temp -> token);
		if (temp -> next)
			printf(" ");
		temp = temp -> next;
	}
	if (!flag)
		printf("\n");
}

void	change_old_pwd(t_shell *shell)
{
	int 	i;
	char 	cwd[PATH_MAX];
	char 	*oldpwd;
	char 	*pwd;
	
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
			break;
		}
		i++;
	}
}

void	change_new_pwd(t_shell *shell)
{
	int 	i;
	char 	cwd[PATH_MAX];
	char 	*oldpwd;
	char 	*pwd;
	
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
			break;
		}
		i++;
	}
}

void	bi_cd(t_token *token)
{
	change_old_pwd(token -> shell);
	if (chdir(token -> next -> token) != 0)
        printf("minishell: cd: %s: No such file or directory\n", token -> next -> token);
	change_new_pwd(token -> shell);
}