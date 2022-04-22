/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:53:53 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/14 14:37:49 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	list_is_sorted(t_exp *head)
{
	t_exp	*cursor;

	cursor = head;
	while (cursor && cursor->next)
	{
		if (ft_strcmp(cursor->key, cursor->next->key) > 0)
			return (0);
		cursor = cursor->next;
	}
	return (1);
}

void	swap_node(t_exp	**env)
{
	t_exp	*swap_1;
	t_exp	*swap_2;

	swap_1 = *env;
	swap_2 = (*env)->next;
	swap_2->prev = swap_1->prev;
	if (swap_2->prev)
		swap_2->prev->next = swap_2;
	swap_1->next = swap_2->next;
	if (swap_1->next)
		swap_1->next->prev = swap_1;
	swap_2->next = swap_1;
	swap_1->prev = swap_2;
}

t_exp	*sort_export(t_exp *env)
{
	while (!list_is_sorted(env))
	{
		while (env->next)
		{
			if (ft_strcmp(env->key, env->next->key) > 0)
				swap_node(&env);
			if (env->next)
				env = env->next;
		}
		while (env->prev)
			env = env->prev;
	}
	return (env);
}
