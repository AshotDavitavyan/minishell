/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:49:50 by vgribkov          #+#    #+#             */
/*   Updated: 2023/06/18 19:50:36 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_env(t_token *token)
{
	int i = 0;
	while (token -> env[i])
	{
		printf("%s\n", token -> env[i++]);
	}
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
	temp = temp -> next;
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

void	bi_cd(t_token *token)
{
	if (chdir(token ->next -> token) != 0)
        perror("chdir");
	
}

int	ft_is_num(char *str)
{
	
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return 0;
		str++;
	}
	return 1;
}

void	bi_exit(t_token *token)
{
	if (!token -> next)
		exit(0);
	if (ft_is_num(token -> next -> token))
		exit(ft_atoi(token -> next -> token));
}