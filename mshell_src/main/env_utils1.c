#include "../../includes/minishell.h"

int	put_global_error(char **new_name, char **name_ptr)
{
	char	*num;
	char	*save;

	num = ft_itoa(global_error);
	save = num;
	(*name_ptr) += 2;
	while (*num != '\0' && *new_name)
	{
		**new_name = *num;
		(*new_name)++;
		num++;
	}
	free(save);
	return (0);
}

char	*move_env(char *env)
{
	while (*env != '=' && env)
		env++;
	env++;
	return (env);
}

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

void	move_ptr(char **name)
{
	char	*sep;

	sep = " <>|&./?@#$%^*-=+,[]{}\'\"";
	if (**name == '$')
		(*name)++;
	while (ft_strchr(sep, **name) == NULL && **name != '\0')
		(*name)++;
}

int	env_len(char *str, char **name)
{
	int	i;

	i = 0;
	move_ptr(name);
	while (*str != '=' && *str)
		str++;
	if (*str == '=')
		str++;
	while (str[i])
		i++;
	return (i);
}
