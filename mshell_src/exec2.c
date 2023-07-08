/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:23 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/08 19:15:40 by vgribkov         ###   ########.fr       */
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

void	close_all(t_token *token, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		close(token -> shell -> fd[i][0]);
		close(token -> shell -> fd[i][1]);
		i++;
	}
}

void	redirector(t_token *token)
{
	int i;

	i = -1;
	if (token -> redirect_flag == 0)
		dup2(open(token -> redirect_fd[ft_strlen_2d_arr(token -> redirect_fd) - 1], O_RDWR, 0644), STDIN_FILENO);
	if (token -> redirect_flag == 1 || token -> redirect_flag == 2)
	{
		while (token -> redirect_fd[++i + 1])
			open(token -> redirect_fd[i], O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (token -> redirect_flag == 1)
			dup2(open(token -> redirect_fd[ft_strlen_2d_arr(token -> redirect_fd) - 1], O_RDWR | O_TRUNC | O_CREAT, 0644), STDOUT_FILENO);
		if (token -> redirect_flag == 2)
			dup2(open(token -> redirect_fd[ft_strlen_2d_arr(token -> redirect_fd) - 1], O_RDWR | O_CREAT, 0644), STDOUT_FILENO);
		// if (token -> redirect_flag == 3)
		
	}
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
		redirector(token);
		close_all(token, j+1);
		execve(true_path(token -> token, token -> shell -> envex), args, token -> shell -> envex);
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
	while (j < i)
	{
		piping(tmp, j++);
		tmp = tmp -> next;
	}
	close_all(tmp1, j);
}

void	exec(t_shell *shell)
{
	if (!shell -> token -> next)
		executing_one(shell -> token -> token, shell -> token -> redirect_fd, shell -> envex, shell);
	else
		exec_n(shell);
}
