/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:29:27 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/20 21:08:07 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (token -> redir_flag_in == 1)
		dup2(open_0(token -> redir_fd_in[ft_strlen_2d_arr(token -> redir_fd_in) - 1]), STDIN_FILENO);
	if (token -> redir_flag_out == 1 || token -> redir_flag_outout == 1)
	{
		if (token -> redir_flag_out == 1)
		{
			while (token -> redir_fd_out[++i + 1])
				open(token -> redir_fd_out[i], O_RDWR | O_TRUNC | O_CREAT, 0644);
		}
		else if (token -> redir_flag_outout == 1)
		{
			while (token -> redir_fd_out[++i + 1])
				open(token -> redir_fd_out[i], O_RDWR | O_CREAT, 0644);
		}
		if (token -> redir_flag_out == 1)
			dup2(open(token -> redir_fd_out[ft_strlen_2d_arr(token -> redir_fd_out) - 1], O_RDWR | O_TRUNC | O_CREAT, 0644), STDOUT_FILENO);
		if (token -> redir_flag_outout == 1)
			dup2(open(token -> redir_fd_out[ft_strlen_2d_arr(token -> redir_fd_out) - 1], O_RDWR | O_CREAT | O_APPEND, 0644), STDOUT_FILENO);
	}
}

// void	redirector_bi(t_token *token)
// {
// 	int i;

// 	i = -1;
// 	if (token -> redir_flag_in == 1)
// 		dup2(open_0(token -> redir_fd_in[ft_strlen_2d_arr(token -> redir_fd_in) - 1]), STDIN_FILENO);
// 	if (token -> redir_flag_out == 1 || token -> redir_flag_outout == 1)
// 	{
// 		if (token -> redir_flag_out == 1)
// 		{
// 			while (token -> redir_fd_out[++i + 1])
// 				open(token -> redir_fd_out[i], O_RDWR | O_TRUNC | O_CREAT, 0644);
// 		}
// 		else if (token -> redir_flag_outout == 1)
// 		{
// 			while (token -> redir_fd_out[++i + 1])
// 				open(token -> redir_fd_out[i], O_RDWR | O_CREAT, 0644);
// 		}
// 		if (token -> redir_flag_out == 1)
// 			dup2(open(token -> redir_fd_out[ft_strlen_2d_arr(token -> redir_fd_out) - 1], O_RDWR | O_TRUNC , 0644), STDOUT_FILENO);
// 		else if (token -> redir_flag_outout == 1)
// 			dup2(open(token -> redir_fd_out[ft_strlen_2d_arr(token -> redir_fd_out) - 1], O_RDWR | O_APPEND, 0644), STDOUT_FILENO);
// 	}
// }