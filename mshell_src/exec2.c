/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:23 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/08 17:28:47 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_n(t_shell *shell)
{
	if (shell -> token -> token)
		;
	return ;
}

void	exec(t_shell *shell)
{
	if (!shell -> token -> next)
		executing_one(shell -> token -> redirect_flag, shell -> token -> token, shell -> token -> redirect_fd[0], shell -> envex);
	else
		exec_n(shell);
}
