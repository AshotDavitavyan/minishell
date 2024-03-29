/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_putstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:33:47 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/28 18:15:08 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_putstr(char *s)
{
	int	i;
	int	flag;

	flag = 1;
	i = 0;
	while (s[i])
	{	
		write(1, &s[i], 1);
		if (s[i] == '=' && flag == 1)
		{
			write(1, "\"", 1);
			flag = 0;
		}
		i++;
	}
	write(1, "\"", 1);
}

void	def_putstr(char *s)
{
	if (!s)
		return ;
	while (*s)
		write(1, s++, 1);
}

void	my_putstr(char *str)
{
	int	i;

	i = 0;
	if (!ft_strchr(str, '='))
	{
		def_putstr(str);
	}
	else
		new_putstr(str);
}
