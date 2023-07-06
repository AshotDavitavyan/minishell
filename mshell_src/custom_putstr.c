/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_putstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:33:47 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/06 09:33:48 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_putstr2(char *s)
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

void	new_putstr(char *s)
{
	int i;
	
	i = 0;
	if (!s)
		return ;
	if (ft_strchr(s, '\''))
	{
		while (s[i])
		{
			if (s[i] == '\'')
			{
				write(1, "\"\"", 2);
				return ;
			}
			write(1, &s[i], 1);
			i++;
		}
	}
	else
		new_putstr2(s);
	
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
	{
		if (ft_strlen(ft_strchr(str, '=')) == 1)
		{
			def_putstr(str);
			def_putstr("\"\"");
		}
		if (ft_strchr(str, '=')[1] == '\"')
			def_putstr(str);
		else if (ft_strchr(str, '=')[1] == '\'')
			new_putstr(str);
		else if (ft_strchr(str, '=')[1] != '\0')
			new_putstr(str);
	}
}