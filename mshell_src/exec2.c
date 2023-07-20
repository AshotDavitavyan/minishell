/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:23 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/20 21:16:29 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pipes(t_shell *shell, int j)
{
	int	i;

	i = 0;
	while (i < j)
		pipe (shell -> fd[i++]);
}

int	count_exec(t_shell *shell)
{
	t_token *tmp;
	int	i;

	i = 0;
	tmp = shell -> token;
	while(tmp)
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
			dup2(token -> here_fd , STDIN_FILENO);
		}
		if (bi_avail(token))
			exit(bi_execution(token));
		else
		{
			close_all(token, i);
			redirector(token);
			execve(true_path(token -> token[0], token -> shell -> envex), token -> token, token -> shell -> envex);
		}
	}
}

void	exec_n(t_shell *shell)
{
	int		i;
	int 	j;
	t_token	*tmp;
	t_token	*tmp1;
	
	tmp = shell -> token;
	tmp1 = tmp;
	j = 0;
	i = count_exec(shell);
	do_pipes(shell, i);	
	while (tmp)
	{
		piping(tmp, j++, i);
		tmp = tmp -> next;
	}
	close_all(tmp1, j);
}

void	waiter(int count)
{
	int	j;
	int	pid;
	int	temp;
	int	status;

	temp = 1;
	j = 0;
	while (j < count)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > temp)
		{
			temp = pid;
			global_error = status / 256;
		}
		j++;
	}
}

void	exec(t_shell *shell)
{	
	if (!shell -> token -> next)
	{
		if (bi_avail(shell -> token))
			bi_execution(shell -> token);
		else
			executing_one(shell);
	}
	else
		exec_n(shell);
	waiter(ft_lstsize_token(shell -> token));
	unlink("here_doc");
}
