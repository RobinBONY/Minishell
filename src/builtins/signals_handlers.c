/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:46:55 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/03 14:59:10 by alakhdar         ###   ########lyon.fr   */
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
	}
}

void	handler_child(int signo)
{
	if (signo == SIGINT)
	{
		write(2, "\n", 1);
	}
	if (signo == SIGQUIT)
		write(2, "Quit: 3\n", 8);
}

void	handler_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		write(2, "\n", 1);
		exit(1);
	}
}
