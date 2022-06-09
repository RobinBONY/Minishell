/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:37:00 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/09 13:24:05 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	validate_arg(char *arg)
{
	char	*cursor;

	if (ft_strlen(arg) == 0)
		return (1);
	cursor = arg;
	if (ft_isdigit(*cursor) || *cursor == '=' || *cursor == '+')
		return (1);
	while (*cursor && (ft_isalnum(*cursor) || *cursor == '_'))
		cursor++;
	if (*cursor == '\0' || *cursor == '=' || !ft_strncmp(cursor, "+=", 2))
		return (0);
	else
		return (1);
}

void	rep_or_app_env(t_var *head, char *str)
{
	t_var	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->key, ft_strlen(tmp->key)) == 0)
		{
			replace_env(head, str);
			return ;
		}
		tmp = tmp->next;
	}
	append_to_list(head, str);
}

void	rep_or_app_exp(t_exp *head, char *str)
{
	t_exp	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->key, ft_strlen(tmp->key)) == 0)
		{
			replace_exp(head, str);
			return ;
		}
		tmp = tmp->next;
	}
	append_to_exp(head, str);
}

void	replace_env(t_var *head, char *str)
{
	t_var	*tmp;
	char	*buff;

	tmp = head;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->key, ft_strlen(tmp->key)) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			if (str)
			{
				buff = get_value(str);
				tmp->value = ft_strdup(buff);
				if (buff)
					free(buff);
			}
			tmp->printable = is_occurring(str);
		}
		tmp = tmp->next;
	}
}

void	replace_exp(t_exp *head, char *str)
{
	t_exp	*tmp;
	char	*buff;

	tmp = head;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->key, ft_strlen(tmp->key)) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			if (str)
			{
				buff = get_value(str);
				tmp->value = ft_strdup(buff);
				if (buff)
					free(buff);
			}
		}
		tmp = tmp->next;
	}
}
