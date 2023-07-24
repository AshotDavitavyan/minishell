#include "minishell.h"

void	init_shell(t_token_small **tokens, t_shell **shell)
{
	t_token_small *ptr;
	(*shell)->token_small = *tokens;
	ptr = *tokens;
	while (ptr != NULL)
	{
		ptr->shell = *shell;
		ptr = ptr->next;
	}
}

void	move_ptr(char **name)
{
	char *sep;

	sep = " <>|&./?@#$%^*-=+,[]{}\'\"";
	if (**name == '$')
		(*name)++;
	while (ft_strchr(sep, **name) == NULL && **name != '\0')
		(*name)++;
}
int	env_len(char *str, char **name)
{
	int i;

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

int	intlen(int to_count)
{
	int i;

	i = 1;
	while (to_count > 9)
	{
		to_count /= 10;
		i++;
	}
	return (i);
}
int	comp_vars_util(char **name, char **var_arr, int i, int j)
{
	if (i != j)
		return (0);
	i = 0;
	while (i < j)
	{
		if ((*name)[i + 1] != (*var_arr)[i])
			return 0;
		i++;
	}
	return (1);
}


int	isnum(char **name)
{
	if ((*name)[1] >= '0' && (*name)[1] <= '9')
	{
		(*name)+=2;
		return (1);
	}
	return (0);
}

int	single_dollar(char **name, char **new_name)
{
	char *sep;

	sep = " <>|&./@#$%^*-=+,[]{}\'\"";
	if (ft_strchr(sep, (*name)[1]) != NULL || (*name)[1] == '\0')
	{
		if (new_name == NULL)
		{
			(*name)++;
			return (1);
		}
		else
		{
			**new_name = **name;
			(*new_name)++;
			(*name)++;
			return (1);
		}
	}
	return (0);
}

int	comp_vars(char **name, char **var_arr, int i, char *sep)
{
	int		j;

	if (single_dollar(name, NULL) == 1)
		return (1);
	if (isnum(name) == 1)
		return (0);
	if ((*name)[1] == '?')
	{
		(*name) += 2;
		return (intlen(global_error));
	}
	while (ft_strchr(sep, (*name)[i]) == NULL && (*name)[i] != '\0')
		i++;
	i--;
	while (*var_arr)
	{
		j = 0;
		while ((*var_arr)[j] != '=')
			j++;
		if (comp_vars_util(name, var_arr, i, j) == 1)
			return (env_len(*var_arr, name));
		var_arr++;
	}
	move_ptr(name);
	return (0);
}

int	quote_dollar(char **name, char **var_arr, int i, char type)
{
	if (type == 39)
	{
		while (**name != type && **name != '\0')
		{
			(*name)++;
			i++;
		}
		(*name)++;
		return (i);
	}
	while (**name != type)
	{
		if (**name == '$')
			i += comp_vars(name, var_arr, 1, " <>|&./?@#$%^*-=+,[]{}\'\"");
		if (**name != type)
		{
			(*name)++;
			i++;
		}
	}
	(*name)++;
	return (i);
}

void	check_var(t_token_small **ptr, int dollar_index, int i)
{
	char	*name_ptr;
	char	*new_name = NULL;

	name_ptr = (*ptr)->name;
	if (dollar_index == -1)
		return ;
	while (*name_ptr)
	{
		if ((*name_ptr == 34 || *name_ptr == 39) && (*ptr)->type != 34)
		{
			i += quote_dollar(&name_ptr, (*ptr)->shell->envex, 0, *(name_ptr++));
			continue ;
		}
		if (*name_ptr == '$')
		{
			i += comp_vars(&name_ptr, (*ptr)->shell->envex, 1, " <>|&./?@#$%^*-=+,[]{}\'\"");
			continue ;
		}
		name_ptr++;
		i++;
	}
	new_name = (char *)ft_calloc((i + 1), 1);
	put_vars(new_name, ptr);
}

void	handle_dollar_signs(t_token_small **tokens)
{
	t_token_small *ptr;

	ptr = *tokens;
	while (ptr != NULL)
	{
		if (ptr->type != 39)
			check_var(&ptr, ft_strchr_num((ptr)->name, '$'), 0);
		if (ft_strlen(ptr->name) == 0)
		{
			ptr = tokendelone(ptr, tokens);
			continue ;
		}
		ptr = ptr->next;
	}
}
