#include "minishell.h"

void	no_vars_match(char *new_name, char *name_ptr)
{
	char *sep;

	sep = " <>|&./?@#$%^*-=+,[]{}\'\"";
	if (ft_strchr(sep, *name_ptr))
	{
		*new_name = '$';
		return ;
	}
}
void	alloc_var(char **new_name, char **name_ptr, char **var_arr, int i)
{
	char	*sep;
	char	*var_ptr;

	sep = " <>|&./?@#$%^*-=+,[]{}\'\"";
	var_ptr = *var_arr;
	if (**name_ptr == '$')
		(*name_ptr)++;
	while (*var_arr)
	{
		i = 0;
		while (*var_ptr != '=' && *var_ptr != '\0')
		{
			i++;
			var_ptr++;
		}
		var_ptr++;
		if (ft_strnncmp(var_arr, name_ptr, i, NULL) == 0)
		{		
			ft_strlcat(*new_name, var_ptr, ft_strlen(var_ptr) + 1);
			return ;
		}
		var_arr++;
		var_ptr = *var_arr;
	}
	no_vars_match(*new_name, *name_ptr);
}
void	alloc_quote_dollar(char **new_name, char **name_ptr, char type, char **var_arr)
{
	type = *(*name_ptr)++;
	if (type == 39)
	{
		while (**name_ptr != type && **name_ptr != '\0')
		{
			**new_name = **name_ptr;
			(*new_name)++;
			(*name_ptr)++;
		}
		return ;
	}
	else if (type == 34)
	{
		while (**name_ptr != type && **name_ptr != '\0')
		{
			if (**name_ptr == '$')
				alloc_var(new_name, name_ptr, var_arr, 0);
			**new_name = **name_ptr;
			(*new_name)++;
			(*name_ptr)++;
		}
	}
}
void	put_vars(char *new_name, t_token **ptr)
{
	char	*name_ptr;

	name_ptr = (*ptr)->name;
	while (*name_ptr)
	{
		if (*name_ptr == 34 || *name_ptr == 39)
		{
			alloc_quote_dollar(&new_name, &name_ptr, 0, (*ptr)->shell->envex);
			continue ;
		}
		if (*name_ptr == '$')
		{
			alloc_var(&new_name, &name_ptr, (*ptr)->shell->envex, 0);
			continue ;
		}
		*new_name = *name_ptr;
		name_ptr++;
		new_name++;
	}
	free((*ptr)->name);
	(*ptr)->name = new_name;
	printf("%s\n", new_name);
}