/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:06:59 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/08 11:17:12 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	set_input(t_cmd *exec, t_source *tmp, t_env *env)
{	
	exec->input = open_infile(replace_var(tmp->next->str, env->head_var));
	tmp->used = 0;
	tmp->next->used = 0;
}

void	set_output(t_cmd *exec, t_source *tmp, int mode, t_env *env)
{
	if (mode)
		exec->output = open_append(replace_var(tmp->next->str, env->head_var));
	else
		exec->output = open_outfile(replace_var(tmp->next->str, env->head_var));
	tmp->used = 0;
	tmp->next->used = 0;
}
