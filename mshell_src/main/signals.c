/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:02:56 by adavitav          #+#    #+#             */
/*   Updated: 2023/07/28 14:03:38 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sighandler(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_global_error = 1;
	(void)signum;
}

void	sighandler2(int signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_global_error = 130;
	(void)signal;
}

void	sighandler3(int signal)
{
	printf("\n");
	(void)signal;
}
