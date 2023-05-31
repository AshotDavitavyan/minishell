/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 07:53:43 by adavitav          #+#    #+#             */
/*   Updated: 2023/02/22 07:56:59 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "stdio.h"

int	ft_print_p(unsigned long long nb, int save)
{
	char		*lc;
	static int	size = 0;

	lc = ft_strdupp("0123456789abcdef");
	size = save;
	if (size == 0)
		size += write(1, "0x", 2);
	if (nb >= 16)
	{
		ft_print_p(nb / 16, size);
		size += ft_putchar (lc[nb % 16]);
	}
	else
		size += ft_putchar (lc[nb % 16]);
	free(lc);
	return (size);
}
