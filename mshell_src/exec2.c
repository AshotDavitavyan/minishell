/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:23 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/10 21:52:04 by vgribkov         ###   ########.fr       */
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

void	piping(t_token *token, int j)
{
	char **args;
	int	f;
	
	f = fork();
	if (f == 0)
	{
		args = ft_split(token -> token, ' ');
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
		if (bi_avail(token))
		{
			fprintf(stderr, "%s\n", token->token);
			bi_execution(token -> shell);
			close_all(token, j + 1);
			exit(0);
		}
		else
		{
			close_all(token, j + 1);
			redirector(token);
			execve(true_path(token -> token, token -> shell -> envex), args, token -> shell -> envex);
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
		piping(tmp, j++);
		tmp = tmp -> next;
	}
	close_all(tmp1, j);
	while (wait(NULL) != -1)
		;
	unlink("here_doc");
}

void	exec(t_shell *shell)
{
	if (!shell -> token -> next)
	{
		if (bi_avail(shell -> token))
			bi_execution(shell);
		else
			executing_one(shell -> token -> token, shell -> token -> redirect_fd, shell -> envex, shell);
	}
	else
		exec_n(shell);
}
