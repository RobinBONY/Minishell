/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_waitpid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:08:52 by rbony             #+#    #+#             */
/*   Updated: 2022/06/09 09:51:03 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_waitpid(t_cmd	*tmp)
{
	while (tmp)
	{
		waitpid(tmp->pid, &g_exit, 0);
		if (g_exit == 2 || g_exit == 3)
			g_exit += 128;
		else if (WIFEXITED(g_exit))
			WEXITSTATUS(g_exit);
		tmp = tmp->next;
	}
}

int	check_redirects(t_cmd *exec)
{
	if (exec->input == -1 || exec->output == -1)
		return (1);
	return (0);
}
