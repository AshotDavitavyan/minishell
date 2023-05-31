/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_check_uc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:08:34 by adavitav          #+#    #+#             */
/*   Updated: 2023/02/24 14:29:33 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hex_check_uc(unsigned int nb, char apple, int save)
{
	char		*uc;
	static int	size = 0;

	uc = ft_strdupp("0123456789ABCDEF");
	size = save;
	if (nb >= 16)
	{
		hex_check_uc(nb / 16, apple, size);
		size += ft_putchar (uc[nb % 16]);
	}
	else
		size += ft_putchar (uc[nb % 16]);
	free(uc);
	return (size);
}
