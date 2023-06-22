/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:04:59 by vgribkov          #+#    #+#             */
/*   Updated: 2023/06/22 18:03:54 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_exit(t_token *token)
{
	if (!token -> next)
		exit(0);
	else if (token -> next -> next)
		printf("minishell: exit: too many arguments\n");
	else if (ft_is_num(token -> next -> token) && long_long_check(token -> next -> token))
		exit(ft_atoi(token -> next -> token));
	printf("minishell: exit: %s: numeric argument required\n", token -> next -> token);
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
	while (tok)
	{
		if (unset_acheck(shell, tok -> token) == 1)
			unset_delete(shell, tok -> token);
		tok = tok -> next;
	}
}




