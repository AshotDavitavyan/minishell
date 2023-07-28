/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:07:01 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/28 14:45:08 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lstsize_token(t_token *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

t_token	*ft_lstlast_token(t_token *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst -> next;
	}
	return (lst);
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*help;

	help = *lst;
	if (!help)
	{
		*lst = new;
		return ;
	}
	help = ft_lstlast_token(help);
	help -> next = new;
}

int	bi_check_exec(t_token *token)
{
	char	**arr;
	int		ret_value;

	ret_value = 0;
	arr = token -> token;
	if (ft_strcmp("env", str_to_lower(arr[0])) == 0)
		ret_value = bi_env(token -> shell);
	else if (ft_strcmp("pwd", str_to_lower(arr[0])) == 0)
		ret_value = bi_pwd();
	else if (ft_strcmp("echo", str_to_lower(arr[0])) == 0)
		ret_value = bi_echo(token);
	else if (ft_strcmp("cd", arr[0]) == 0)
		ret_value = bi_cd(token);
	else if (ft_strcmp("export", str_to_lower(arr[0])) == 0)
		ret_value = bi_export1(token -> shell);
	else if (ft_strcmp("unset", str_to_lower(arr[0])) == 0)
		ret_value = bi_unset(token -> shell);
	else if (ft_strcmp("exit", str_to_lower(arr[0])) == 0)
		ret_value = bi_exit(token);
	return (ret_value);
}

int	bi_execution(t_token *token)
{
	int		ret_value;
	char	**arr;
	int		f;

	arr = token -> token;
	if (token -> redir_flag_out + token -> redir_flag_outout + token
		-> redir_flag_in == 1 && (ft_strcmp("exit", arr[0]) == 0))
	{
		ret_value = bi_check_exec(token);
		return (ret_value);
	}	
	if (token -> redir_flag_out + token
		-> redir_flag_outout + token -> redir_flag_in == 0)
	{
		ret_value = bi_check_exec(token);
		return (ret_value);
	}
	f = fork();
	if (f != 0)
		return (0);
	ret_value = 0;
	redirector(token);
	ret_value = bi_check_exec(token);
	g_global_error = ret_value;
	exit(ret_value);
}
