/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:46:55 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/26 15:34:22 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handler(int signo)
{
	if (signo == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit = 1;
	}
	if (signo == SIGUSR1)
	{
		printf("exit\n");
		exit (1);
	}
	if (signo == SIGQUIT)
		signal(SIGQUIT, SIG_DFL);
}

void	error_exit(char *msg, int exit_code)
{
	g_exit = exit_code;
	ft_putstr_fd(msg, 1);
	exit(exit_code);
}
