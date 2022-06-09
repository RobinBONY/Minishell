/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:33:01 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/09 13:34:12 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	unset_exp(t_exp *head_exp, char *key)
{
	t_exp	*cursor;
	t_exp	*prev;

	cursor = head_exp;
	if (cursor != NULL && ft_strcmp(cursor->key, key) == 0)
	{
		head_exp = cursor->next;
		free(cursor->key);
		if (cursor->value)
			free(cursor->value);
		free(cursor);
		return ;
	}
	while (cursor != NULL && ft_strcmp(cursor->key, key) != 0)
	{
		prev = cursor;
		cursor = cursor->next;
	}
	if (cursor == NULL)
		return ;
	prev->next = cursor->next;
	free(cursor->key);
	if (cursor->value)
		free(cursor->value);
	free(cursor);
}

void	unset_env(t_var *head_env, char *key)
{
	t_var	*cursor;
	t_var	*prev;

	cursor = head_env;
	if (cursor != NULL && ft_strcmp(cursor->key, key) == 0)
	{
		head_env = cursor->next;
		free(cursor->key);
		if (cursor->value)
			free(cursor->value);
		free(cursor);
		return ;
	}
	while (cursor != NULL && ft_strcmp(cursor->key, key) != 0)
	{
		prev = cursor;
		cursor = cursor->next;
	}
	if (cursor == NULL)
		return ;
	prev->next = cursor->next;
	free(cursor->key);
	if (cursor->value)
		free(cursor->value);
	free(cursor);
}

int	ft_unset(t_exp *head_exp, t_var *head_env, char *key)
{
	unset_env(head_env, key);
	unset_exp(head_exp, key);
	return (0);
}
