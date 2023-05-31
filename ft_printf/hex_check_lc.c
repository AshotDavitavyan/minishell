/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_check_lc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:04:38 by adavitav          #+#    #+#             */
/*   Updated: 2023/02/21 13:40:21 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hex_check_lc(unsigned int nb, char apple, int save)
{
	char		*lc;
	static int	size = 0;

	lc = ft_strdupp("0123456789abcdef");
	size = save;
	if (nb >= 16)
	{
		hex_check_lc(nb / 16, apple, size);
		size += ft_putchar (lc[nb % 16]);
	}
	else
		size += ft_putchar (lc[nb % 16]);
	free(lc);
	return (size);
}
