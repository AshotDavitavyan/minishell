/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:49:50 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/19 13:59:19 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_env(t_shell *shell)
{
	int i = 0;
	while (shell -> envex[i])
	{
		if (ft_strchr(shell -> envex[i], '='))
			printf("%s\n", shell -> envex[i]);
		i++;
	}
	return (0);
}

int	ft_isletter(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	validation(char **arr)
{
	int j = 0;
	
	if (arr[++j])
	{
		if (ft_isletter(arr[j][0]) == 0)
		{
			printf("bash: export: `%s': not a valid identifier\n", arr[j]);
			return (1);
		}
	}
	return (1);
}

int	bi_export1(t_shell *shell)	
{
	int	i;
	char **arr;
	int ret_val;
	
	arr = token -> token;
	i = 0;
	if (!arr[1])
	{
		while (shell -> envex[i])
		{
			def_putstr("declare -x ");
			my_putstr(shell -> envex[i]);
			printf("\n");
			i++;
		}
		return (0);
	}
	if (validation(arr) == 0)
		return (1);
	ret_val = bi_export2(shell, arr);
	return (ret_val);
}

int	bi_pwd(void)
{
	char cwd[PATH_MAX];
	
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return (0);
}

int	bi_echo(t_token *token)
{
	char **arr;
	int flag;
	int	i;

	arr = token -> token;
	i = 0;
	if (ft_strcmp(arr[1], "-n") == 0)
		flag = 1;
	else
		flag = 0;
	if (flag)
		arr++;
	while(arr[++i])
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
	global_error = 1;
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
}

int	bi_cd(t_token *token)
{
	char **arr;
	DIR	*tmp;
	
	arr = token -> token;
	if (access(arr[1], F_OK))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arr[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(arr[1], 2);
			ft_putstr_fd("/: Permission denied\n", 2);
			return (1);
		}
		change_old_pwd(token -> shell);
		change_new_pwd(token -> shell);
	}
	return (0);
}

int	ft_strlen_2d_arr(char **arr)
{
	int	i;

	i = -1;
	while(arr[++i]);
	return (i);
}