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

void	do_plus_plus(size_t *i, char **s1, char **s2)
{
	(*i)++;
	(*s1)++;
	(*s2)++;
}
void	ft_strnncmp_util(char **s2, int *to_return)
{
	if (to_return != NULL)
		*to_return = 0;
	while (**s2 != '\0')
		(*s2)++;
}
int	ft_strnncmp(char **s1, char **s2, size_t n, int *to_return)
{
	size_t	i;
	char	**save_s2;
	char	*save_s1;

	i = 0;
	save_s1 = *s1;
	save_s2 = s2;
	if (**s2 == '$')
		(*s2)++;
	while ((**s1 || **s2) && i < n)
	{
		if (**s1 != **s2)
		{
			if (*(s1 + 1) != NULL)
				s2 = save_s2;
			else
				ft_strnncmp_util(s2, to_return);
			*s1 = save_s1;
			return (-1);
		}
		do_plus_plus(&i, s1, s2);
	}
	*s1 = save_s1;
	return (0);
}