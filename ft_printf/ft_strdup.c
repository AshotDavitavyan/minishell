/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:18:32 by adavitav          #+#    #+#             */
/*   Updated: 2023/02/21 13:36:36 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdupp(char *s1)
{
	int		count;
	char	*ptr;

	count = 0;
	ptr = (char *)malloc(17 * sizeof(char));
	if (!ptr)
		return (NULL);
	while (16 > count)
	{
		ptr[count] = s1[count];
		count++;
	}
	return (ptr);
}
