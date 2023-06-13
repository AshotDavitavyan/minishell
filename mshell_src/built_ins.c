/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:49:50 by vgribkov          #+#    #+#             */
/*   Updated: 2023/06/12 16:07:02 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
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
	if (ft_strncmp("-n", token -> next -> token, 3) == 0)
	{
		flag = 1;
		temp = temp -> next;
	}
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

