/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:11:18 by adavitav          #+#    #+#             */
/*   Updated: 2023/07/05 11:33:20 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	loc;

	loc = (char)c;
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == loc)
			return ((char *)s);
		s++;
	}
	if (*s == loc)
		return ((char *)s);
	return (NULL);
}
