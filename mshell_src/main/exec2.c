/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:23 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/24 18:04:03 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_pipes(t_shell *shell, int j)
{
	int	i;

	i = 0;
	while (i < j)
		pipe (shell -> fd[i++]);
}

int	count_exec(t_shell *shell)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = shell -> token;
	while (tmp)
	{
		tmp = tmp -> next;
		i++;
	}
	return (i);
}

void	pipes_dups(t_token *token, int j)
{
	if (j == 0)
	{
		dup2(token -> shell -> fd[j][1], STDOUT_FILENO);
	}
	else if (!token -> next)
	{
		dup2(token -> shell -> fd[j - 1][0], STDIN_FILENO);
	}
	else
	{
		dup2(token -> shell -> fd[j][1], STDOUT_FILENO);
		dup2(token -> shell -> fd[j - 1][0], STDIN_FILENO);
	}
}

void	piping(t_token *token, int j, int i)
{
	int	f;

	here_doc_looper(token);
	f = fork();
	if (f == 0)
	{
		global_error = 0;
		pipes_dups(token, j);
		if (token -> here_doc_flag == 1)
		{
			token -> here_fd = open("here_doc", O_RDWR, 0644);
			dup2(token -> here_fd, STDIN_FILENO);
		}
		if (bi_avail(token))
			exit(bi_execution(token));
		else
		{
			close_all(token, i);
			redirector(token);
			execve(true_path(token -> token[0], token -> shell -> envex), token
				-> token, token -> shell -> envex);
			f_error(true_path(token -> token[0], token -> shell -> envex));
		}
	}
}

void	fork_failed_error()
{
	ft_putstr_fd("minishell: fork: ", 2);
	ft_putstr_fd("Resource temporarily unavailable\n", 2);
	global_error = 1;
}
void	exec_n(t_shell *shell)
{
	int		i;
	int		j;
	t_token	*tmp;
	t_token	*tmp1;

	tmp = shell -> token;
	tmp1 = tmp;
	j = 0;
	i = count_exec(shell);
	if (i > 400)
	{
		fork_failed_error();
		return ;
	}
	do_pipes(shell, i);
	while (tmp)
	{
		piping(tmp, j++, i);
		tmp = tmp -> next;
	}
	close_all(tmp1, j);
}
