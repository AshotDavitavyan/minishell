/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:23 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/06 10:33:41 by vgribkov         ###   ########.fr       */
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

int	bi_avail(t_shell *shell)
{
	if (ft_strncmp("env", shell -> token -> token, 3) == 0 ||
		ft_strncmp("pwd", shell -> token -> token, 3) == 0 ||
		ft_strncmp("echo", shell -> token -> token, 4) == 0 ||
		ft_strncmp("cd", shell -> token -> token, 2) == 0 ||
		ft_strncmp("exit", shell -> token -> token, 4) == 0 ||
		ft_strncmp("export", shell -> token -> token, 6) == 0 ||
		ft_strncmp("unset", shell -> token -> token, 5) == 0 ||
		ft_strncmp("env ", shell -> token -> token, 4) == 0 ||
		ft_strncmp("pwd ", shell -> token -> token, 4) == 0 ||
		ft_strncmp("echo ", shell -> token -> token, 5) == 0 ||
		ft_strncmp("cd ", shell -> token -> token, 3) == 0 ||
		ft_strncmp("exit ", shell -> token -> token, 5) == 0 ||
		ft_strncmp("export ", shell -> token -> token, 7) == 0 ||
		ft_strncmp("unset ", shell -> token -> token, 6) == 0
		)
		{
			return (1);
		}
		return (0);
}