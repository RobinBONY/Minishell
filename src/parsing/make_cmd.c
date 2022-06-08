/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:37:39 by rbony             #+#    #+#             */
/*   Updated: 2022/06/08 11:36:32 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_cmd	*make_command(t_source **source, t_env *env, t_cmd *prev)
{
	int			len;
	t_cmd		*new;

	len = get_len(*source);
	if (len > 0)
	{
		new = malloc(sizeof(t_cmd));
		if (!new)
			return (NULL);
		new->input = 0;
		new->output = 0;
		new->heredocs = NULL;
		if (find_redirects(new, source, env))
			return (free_executor(new));
		if (place_env_var(*source, env->head_var))
			return (free_executor(new));
		if (set_cmd(source, new, prev, len))
			return (free_executor(new));
	}
	return (new);
}
