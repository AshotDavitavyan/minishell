/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:09:49 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/25 18:28:16 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	here_d(t_token *token, int j)
{
	char	*str;

	token -> here_fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0664);
	while (1)
	{
		if (global_error == 1)
			break ;
		str = readline("> ");
		if (global_error == 1)
			break ;
		if (global_error)
			break ;
		if (!str)
		{
			free(str);
			write(1, "> ", 2);
			global_error = 0;
			break ;
		}
		if (ft_strcmp(str, token -> sep_arr[j]) == 0)
		{
			free(str);
			break ;
		}
		//printf("%d\n", global_error);
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
		global_error = 1;
		exit(1);
	}
	return (fd);
}

void	openh_dup2(int fd)
{
	fd = open("here_doc", O_RDWR, 0644);
	dup2(fd, STDIN_FILENO);
}

