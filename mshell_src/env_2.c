#include "minishell.h"

void	init_env(t_shell **shell, char **envp)
{
	int	i = 0;
	while (envp[i])
		i++;
	(*shell) -> envex = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("OLDPWD", envp[i], 6) == 0)
			(*shell) -> envex[i] = ft_strdup("OLDPWD");
		else
			(*shell) -> envex[i] = ft_strdup(envp[i]);
	}
	(*shell) -> envex[i] = NULL;
}

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

size_t	ft_strlcat_dollar(char **name_new, const char *src, size_t destsize, char **name_ptr)
{
	size_t	destlen;
	size_t	srclen;
	char	*dest;

	dest = *name_new;
	if ((!dest && destsize == 0) || (!src && destsize == 0))
		return (0);
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	if (destlen >= destsize)
		return (destsize + srclen);
	if (destsize - destlen <= srclen)
	{
		ft_memcpy(dest + destlen, src, srclen);
		dest[destsize - 1] = '\0';
	}
	else
		ft_memcpy(dest + destlen, src, srclen + 1);
	move_ptr(name_ptr);
	(*name_new) += ft_strlen(src);
	return (destlen + srclen);
}

int	alloc_vars(char **name, char **var_arr, char **new_name, char *sep)
{
	int	j;
	int	i;

	i = 1;
	if (single_dollar(name, new_name) == 1)
		return (0);
	if (isnum(name) == 1)
		return (0);
	if ((*name)[1] == '?')
		return (put_global_error(new_name, name));
	while (ft_strchr(sep, (*name)[i]) == NULL && (*name)[i] != '\0')
		i++;
	i--;
	while (*var_arr)
	{
		j = 0;
		while ((*var_arr)[j] != '=')
			j++;
		if (comp_vars_util(name, var_arr, i, j) == 1)
			return (ft_strlcat_dollar(new_name, move_env(*var_arr), ft_strlen(move_env(*var_arr)) + 1, name));
		var_arr++;
	}
	move_ptr(name);
	return (0);
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
		(*name_ptr)++;
		return ;
	}
	else if (type == 34)
	{
		while (**name_ptr != type && **name_ptr != '\0')
		{
			if (**name_ptr == '$')
				alloc_vars(name_ptr, var_arr, new_name, " <>|&./?@#$%^*-=+,[]{}\'\"");
			**new_name = **name_ptr;
			(*new_name)++;
			(*name_ptr)++;
		}
	}
}
void	put_vars(char *new_name, t_token_small **ptr)
{
	char	*name_ptr;
	char	*save;

	name_ptr = (*ptr)->name;
	save = new_name;
	while (*name_ptr)
	{
		if ((*name_ptr == 34 || *name_ptr == 39) && (*ptr)->type != 34)
		{
			alloc_quote_dollar(&new_name, &name_ptr, 0, (*ptr)->shell->envex);
			continue ;
		}
		if (*name_ptr == '$')
		{
			alloc_vars(&name_ptr, (*ptr)->shell->envex, &new_name, " <>|&./?@#$%^*-=+,[]{}\'\"");
			continue ;
		}
		*new_name = *name_ptr;
		name_ptr++;
		new_name++;
	}
	*new_name = '\0';
	new_name = save;
	free((*ptr)->name);
	(*ptr)->name = new_name;
	(*ptr)->var_flag = 1;
}
