/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:56:05 by adavitav          #+#    #+#             */
/*   Updated: 2023/02/21 12:56:14 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	negative_int(void)
{
	write (1, "-2147483648", 11);
	return (11);
}

int	ft_putnbr(int nb, int save)
{
	static int	size = 0;

	size = save;
	if (nb == -2147483648)
		return (negative_int());
	if (nb < 0)
	{
		write (1, "-", 1);
		size += 1;
		nb = nb * -1;
	}
	if (nb > 9)
	{
		ft_putnbr (nb / 10, size);
		ft_putchar ((nb % 10) + '0');
		size += 1;
	}
	else
	{
		ft_putchar (nb + '0');
		size += 1;
	}
	return (size);
}
