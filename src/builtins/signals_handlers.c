/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:46:55 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/08 16:53:27 by alakhdar         ###   ########lyon.fr   */
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
		seum_exit();
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

void	seum_exit(void)
{
	// if (WIFEXITED(g_exit))
	// 	g_exit = WEXITSTATUS(g_exit);
	// // if (WIFSIGNALED(g_exit))
	// // 	g_exit += WTERMSIG(g_exit);
	if (WIFEXITED(g_exit))
	{
		if (WEXITSTATUS(g_exit) == SIGINT)
		{
			printf("%d\n", WEXITSTATUS(g_exit));
			g_exit = 130;
		}
		if (WEXITSTATUS(g_exit) == SIGQUIT)
			g_exit = 131;
	}
}
