/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:09:49 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/27 18:38:18 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	here_d(t_token *token, int j)
{
	char	*str;

	token -> here_fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0664);
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			free(str);
			write(1, "> ", 2);
			g_global_error = 0;
			break ;
		}
		if (ft_strcmp(str, token -> sep_arr[j]) == 0)
		{
			free(str);
			break ;
		}
		write(token -> here_fd, str, ft_strlen(str));
		write(token -> here_fd, "\n", 1);
		free(str);
	}
	close(token -> here_fd);
}

void	here_doc_looper(t_token *token)
{
	int	j;

	j = 0;
	while (token -> here_doc_flag == 1 && token -> sep_arr[j])
	{
		here_d(token, j);
		j++;
	}
}

int	open_0(char *argv)
{
	int	fd;

	fd = open(argv, O_RDWR, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_global_error = 1;
		exit(1);
	}
	return (fd);
}

void	openh_dup2(int fd)
{
	fd = open("here_doc", O_RDWR, 0644);
	dup2(fd, STDIN_FILENO);
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
