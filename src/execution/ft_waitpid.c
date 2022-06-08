/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_waitpid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:08:52 by rbony             #+#    #+#             */
/*   Updated: 2022/06/08 10:48:42 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_waitpid(t_cmd	*tmp)
{
	while (tmp)
	{
		waitpid(tmp->pid, &g_exit, 0);
		if (WIFEXITED(g_exit))
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
