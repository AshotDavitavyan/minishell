/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:28:23 by adavitav          #+#    #+#             */
/*   Updated: 2023/05/20 12:36:43 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ft_placeholder(const char *apple, va_list ptr)
{
	int	size;

	size = 0;
	if (*apple == 'c')
		size = ft_putchar(va_arg(ptr, int));
	else if (*apple == '%')
		size = ft_putchar(*apple);
	else if (*apple == 's')
		size = ft_putstr(va_arg(ptr, char *));
	else if (*apple == 'd' || *apple == 'i')
		size = ft_putnbr(va_arg(ptr, int), 0);
	else if (*apple == 'u')
		size = ft_putnbr_u(va_arg(ptr, unsigned int), 0);
	else if (*apple == 'x')
		size = hex_check_lc(va_arg(ptr, unsigned int), *apple, 0);
	else if (*apple == 'X')
		size = hex_check_uc(va_arg(ptr, unsigned int), *apple, 0);
	else if (*apple == 'p')
		size = ft_print_p(va_arg(ptr, unsigned long long), 0);
	return (size);
}

int	ft_printf(const char *apple, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, apple);
	i = 0;
	while (*apple)
	{
		while (*apple == '%')
		{
			apple++;
			i += ft_placeholder(apple, ap);
			apple++;
		}
		if (*apple)
		{
			write(1, &*apple, 1);
			i++;
		}
		apple += (*apple != '\0');
	}
	va_end(ap);
	return (i);
}
