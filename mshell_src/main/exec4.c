/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:10:55 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/25 18:48:05 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	red_out_outout(t_shell *shell, int i)
{
	if (shell -> token -> redir_flag_out == 1)
	{
		while (shell -> token -> redir_fd_out[++i + 1])
			open(shell -> token -> redir_fd_out[i],
				O_RDWR | O_TRUNC | O_CREAT, 0644);
		dup2(open(shell->token->redir_fd_out[ft_strlen_2d_arr(shell
					->token->redir_fd_out) - 1], O_RDWR
				| O_TRUNC | O_CREAT, 0644), STDOUT_FILENO);
	}
	if (shell -> token -> redir_flag_outout == 1)
	{
		while (shell -> token -> redir_fd_out[++i + 1])
			open(shell -> token -> redir_fd_out[i], O_RDWR | O_CREAT, 0644);
		dup2(open(shell->token->redir_fd_out[ft_strlen_2d_arr(shell
					->token->redir_fd_out) - 1], O_RDWR
				| O_CREAT | O_APPEND, 0644), STDOUT_FILENO);
	}
}

void	quit(int sig)
{
	(void)sig;
	global_error = 131;
	ft_putstr_fd("Quit: 3\n", 1);	
}

void	executing_one(t_shell *shell)
{
	int	f;
	int	i;

	here_doc_looper(shell -> token);
	i = -1;
	signal(SIGQUIT, quit);
	signal(SIGINT, sighandler2);
	f = fork();
	if (f == 0)
	{
		if (shell -> token -> redir_flag_in == 1)
			dup2(open_0(shell -> token -> redir_fd_in[ft_strlen_2d_arr(shell
						-> token -> redir_fd_in) - 1]), STDIN_FILENO);
		red_out_outout(shell, i);
		if (shell -> token -> here_doc_flag == 1)
			openh_dup2(shell -> token -> here_fd);
		execve(true_path(shell -> token -> token[0], shell -> envex), shell -> token -> token, shell -> envex);
		f_error(true_path(shell -> token -> token[0], shell -> envex));
	}
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
	global_error = 0;
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
