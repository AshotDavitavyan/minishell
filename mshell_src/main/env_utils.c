#include "minishell.h"

int	ft_strchr_num(const char *s, int c)
{
	char	loc;
	int		i;

	loc = (char)c;
	i = 0;
	while (*s != '\0')
	{
		if (*s == loc)
			return (i);
		s++;
		i++;
	}
	if (*s == loc)
		return (i);
	return (-1);
}
