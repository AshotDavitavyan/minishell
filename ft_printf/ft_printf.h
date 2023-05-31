/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:51:40 by adavitav          #+#    #+#             */
/*   Updated: 2023/02/22 07:52:18 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

int		ft_putchar(char c);
int		ft_putstr(char *c);
int		negative_int(void);
int		ft_putnbr(int nb, int save);
int		ft_putnbr_u(unsigned int nb, int save);
int		ft_placeholder(const char *apple, va_list ptr);
int		ft_printf(const char *apple, ...);
int		hex_check_uc(unsigned int nb, char apple, int save);
int		hex_check_lc(unsigned int nb, char apple, int save);
int		ft_print_p(unsigned long long nb, int save);
char	*ft_strdupp(char *s1);

#endif
