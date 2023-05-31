/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:58:02 by adavitav          #+#    #+#             */
/*   Updated: 2023/02/21 12:52:32 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_u(unsigned int nb, int save)
{
	static int	size = 0;

	size = save;
	if (nb > 9)
	{
		ft_putnbr_u (nb / 10, size);
		ft_putchar ((nb % 10) + '0');
		size += 1;
	}
	else
	{
		ft_putchar(nb + '0');
		size += 1;
	}
	return (size);
}
