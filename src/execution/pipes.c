/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:30:47 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/25 13:35:46 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	close_pipes_fromlast(t_cmd *cmd)
{
	while (cmd->prev)
	{
		cmd = cmd->prev;
		close(cmd->pipex[0]);
		close(cmd->pipex[1]);
	}
}

void	close_pipes_fromfirst(t_cmd *cmd)
{
	while (cmd->next)
	{
		cmd = cmd->next;
		close(cmd->pipex[0]);
		close(cmd->pipex[1]);
	}
}

int	open_pipes(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (pipe(tmp->pipex) == -1)
		{
			close_pipes_fromlast(tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
