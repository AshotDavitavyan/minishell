#include "../../includes/minishell.h"

void	util_dollar(char **new_name, char **name_ptr)
{
	**new_name = **name_ptr;
	(*new_name)++;
	(*name_ptr)++;
}

int	intlen(int to_count)
{
	int	i;

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
			return (0);
		i++;
	}
	return (1);
}

int	isnum(char **name)
{
	if ((*name)[1] >= '0' && (*name)[1] <= '9')
	{
		(*name) += 2;
		return (1);
	}
	return (0);
}

void	init_shell(t_token_small **tokens, t_shell **shell)
{
	t_token_small	*ptr;

	(*shell)->token_small = *tokens;
	ptr = *tokens;
	while (ptr != NULL)
	{
		ptr->shell = *shell;
		ptr = ptr->next;
	}
}
