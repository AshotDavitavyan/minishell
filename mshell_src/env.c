#include "minishell.h"

void	init_shell(t_token **tokens, t_shell **shell)
{
	t_token *ptr;
	(*shell)->token = *tokens;
	ptr = *tokens;
	while (ptr != NULL)
	{
		ptr->shell = *shell;
		ptr = ptr->next;
	}
}

int	comp_vars(char **name, char **var_arr, int i, int to_return)
{
	char	*sep;
	char	*arr_ptr;

	sep = " <>|&./?@#$%^*-=+,[]{}\'\"";
	while (ft_strchr(sep, **name) == NULL && **name != '\0')
	{
		to_return++;
		(*name)++;
	}
	while (*var_arr)
	{
		i = 0;
		arr_ptr = *var_arr;
		while (*arr_ptr != '=' && *arr_ptr)
		{
			arr_ptr++;
			i++;
		}
		if (ft_strnncmp(var_arr, name, i, &to_return) == 0)
			return (ft_strlen(arr_ptr));
		var_arr++;
	}
	return (to_return);
}

int	quote_dollar(char **name, char **var_arr)
{
	char	type;
	int		i;

	type = *(*name)++;
	i = 0;
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
			i += comp_vars(name, var_arr, 0, 0);
		(*name)++;
		i++;
	}
	(*name)++;
	return (i);
}

void	check_var(t_token **ptr, int dollar_index, int i)
{
	char	*name_ptr;

	name_ptr = (*ptr)->name;
	if (dollar_index == -1)
		return ;
	while (*name_ptr)
	{
		if (*name_ptr == 34 || *name_ptr == 39)
		{
			i += quote_dollar(&name_ptr, (*ptr)->shell->envex);
			continue ;
		}
		if (*name_ptr == '$')
		{
			i += comp_vars(&name_ptr, (*ptr)->shell->envex, 0, 0);
			continue ;
		}
		name_ptr++;
		i++;
	}
	name_ptr = (char *)malloc((i + 1) * sizeof(char));
	put_vars(name_ptr, ptr);
}

void	handle_dollar_signs(t_token **tokens)
{
	t_token *ptr;

	ptr = *tokens;
	while (ptr != NULL)
	{
		if (ptr->type != 39)
			check_var(&ptr, ft_strchr_num((ptr)->name, '$'), 0);
		ptr = ptr->next;
	}
}