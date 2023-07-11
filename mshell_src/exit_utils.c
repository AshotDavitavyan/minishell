/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:44:42 by vgribkov          #+#    #+#             */
/*   Updated: 2023/06/19 15:12:08 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_num(char *str)
{
	
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return 0;
		str++;
	}
	return 1;
}

unsigned long long	atoulli(const char *str)
{
	unsigned long long	mult;
	unsigned long long	res;

	mult = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		mult *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += (*str - '0');
		str++;
		if (res > 9223372036854775807)
			return (0);
	}
	return (1);
}

int	long_long_check(char *number)
{
	if (ft_strncmp("-9223372036854775808", number, 21) == 0)//−9,223,372,036,854,775,808
		return (1);
	if (*number == '-')
		number++;
	return(atoulli(number));
}