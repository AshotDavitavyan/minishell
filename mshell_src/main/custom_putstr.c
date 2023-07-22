/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_putstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:33:47 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/07 11:28:07 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_putstr(char *s)
{
	int i;
	
	i = 0;
	while (s[i])
	{
		
		write(1, &s[i], 1);
		if (s[i] == '=')
			write(1, "\"", 1);
		i++;
	}
	write(1, "\"", 1);
}

void	def_putstr(char *s)
{
	if (!s)
		return ;
	while(*s)
		write(1, s++, 1);
}

void	my_putstr(char *str)
{
	int i;

	i = 0;
	if (!ft_strchr(str, '='))
	{
		def_putstr(str);
		write(1, "=\"\"", 3);
	}
	else
		new_putstr(str);
}