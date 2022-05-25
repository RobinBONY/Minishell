/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:06:59 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/25 13:36:13 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	set_input(t_executor *exec, t_source *tmp)
{
	exec->input = open_infile(tmp->next->str);
	tmp->used = 0;
	tmp->next->used = 0;
}

void	set_output(t_executor *exec, t_source *tmp, int mode)
{
	if (mode)
		exec->output = open_append(tmp->next->str);
	else
		exec->output = open_outfile(tmp->next->str);
	tmp->used = 0;
	tmp->next->used = 0;
}
