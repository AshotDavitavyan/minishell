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

int	env_len(char *str)
{
	int i;

	i = 0;
	while (*str != '=' && *str)
		str++;
	if (*str == '=')
		str++;
	while (str[i])
		i++;
	return (i);
}

int	comp_vars_util(char **name, char **var_arr, int i, int j)
{
	if (i != j)
		return (0);
	i = 0;
	while (i < j)
	{
		if (*name[i] != *var_arr[i])
			return 0;
		i++;
	}
	return (1);
}

int	comp_vars(char **name, char **var_arr)
{
	int		j;
	int		i;
	char	*sep;

	j = 0;
	i = 1;
	sep = " <>|&./?@#$%^*-=+,[]{}\'\"";
	if (*name[1] = '?')
		return ()
	while (ft_strchr(sep, *name[i]) == NULL && *name[i] != '\0')
		i++;
	i--;
	while (*var_arr)
	{
		while (*var_arr[j] != '=')
			j++;
		if (comp_vars_util(name, var_arr, i, j) == 1)
			return (env_len(*var_arr));
		var_arr++;
	}
}

int	quote_dollar(char **name, char **var_arr, int i, char type)
{
	if (type == 39)
	{
		while (**name != type)
		{
			(*name)++;
			i++;
		}
		return (i);
	}
	while (**name != type)
	{
		if (**name == '$')
			i += comp_vars(name, var_arr);
		(*name)++;
		i++;
	}
	(*name)++;
	return (i);
}

void	check_var(t_token_small **ptr, int dollar_index, int i)
{
	char	*name_ptr;

	name_ptr = (*ptr)->name;
	if (dollar_index == -1)
		return ;
	while (*name_ptr)
	{
		if (*name_ptr == 34 || *name_ptr == 39)
		{
			i += quote_dollar(&name_ptr, (*ptr)->shell->envex, 0, *name_ptr++);
			continue ;
		}
		if (*name_ptr == '$')
		{
			i += comp_vars(&name_ptr, (*ptr)->shell->envex);
			continue ;
		}
		name_ptr++;
		i++;
	}
	name_ptr = (char *)malloc((i + 1) * sizeof(char));
	put_vars(name_ptr, ptr);
}

void	handle_dollar_signs(t_token_small **tokens)
{
	t_token_small *ptr;

	ptr = *tokens;
	while (ptr != NULL)
	{
		if (ptr->type != 39)
			check_var(&ptr, ft_strchr_num((ptr)->name, '$'), 0);
		ptr = ptr->next;
	}
}
