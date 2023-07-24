/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:49:50 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/24 11:36:57 by vgribkov         ###   ########.fr       */
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

int	validation(char **str)
{
	int		i;
	int		j;
	char	*del;

	del = "<>|&./?@#$%^*-,[]{}\'\"";
	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (del[j])
		{
			if (ft_strchr(dup_bef_eq(str[i]), del[j]) || ft_isdigit(str[i][0]) == 1)
			{
				ft_putstr_fd("minishell: \'", 2);
				ft_putstr_fd(str[i], 2);
				ft_putstr_fd("\': not a valid identifier\n", 2);
				global_error = 1;
				return (-1);
			}
			j++;
		}
		i++;
	}
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
	if (validation(arr) == 0)
		return (1);
	ret_val = bi_export2(shell, arr);
	return (ret_val);
}

int	bi_pwd(void)
{
	char	cwd[PATH_MAX];

	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return (0);
}
