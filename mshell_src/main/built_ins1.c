/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:49:50 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/28 14:53:47 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bi_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell -> envex[i])
	{
		if (ft_strchr(shell -> envex[i], '='))
			printf("%s\n", shell -> envex[i]);
		i++;
	}
	return (0);
}

int	ft_isletter(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

void	error_nvi(char *str)
{
	ft_putstr_fd("minishell: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	g_global_error = 1;
}

int	validation(char **str)
{
	int		i;
	int		j;
	char	*del;
	char	*temp;

	del = "!()<>|&./?@#$%^*-,[]{}\'\"";
	i = 1;
	temp = dup_bef_eq(str[i]);
	while (str[i])
	{
		j = 0;
		while (del[j])
		{
			if (ft_strchr(temp, del[j]) || ft_isdigit(str[i][0]) == 1)
			{
				error_nvi(str[i]);
				free(temp);
				return (-1);
			}
			j++;
		}
		i++;
	}
	free(temp);
	return (1);
}

int	bi_export1(t_shell *shell)
{
	int		i;
	char	**arr;
	int		ret_val;

	arr = shell -> token -> token;
	i = 0;
	if (!arr[1])
	{
		while (shell -> envex[i])
		{
			def_putstr("declare -x ");
			my_putstr(shell -> envex[i]);
			printf("\n");
			i++;
		}
		return (0);
	}
	if (validation(arr) == -1)
		return (1);
	ret_val = bi_export2(shell, arr, 0);
	return (ret_val);
}
