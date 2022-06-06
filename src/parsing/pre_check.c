/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:15:26 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/06 16:11:42 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_quotes(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (*tmp == '\'')
		{
			tmp = ft_strchr(tmp, '\'');
			if (!tmp)
				return (unclosed_quote('\''));
		}
		else if (*tmp == '"')
		{
			tmp = ft_strchr(tmp, '"');
			if (!tmp)
				return (unclosed_quote('"'));
		}
		tmp++;
	}
	return (0);
}

int	not_interpreted(char *line)
{
	if (check_quotes(line))
		return (1);
	if (ft_strchr(line, ';'))
		return (unmanaged_character_error(';'));
	if (ft_strchr(line, '\\'))
		return (unmanaged_character_error('\\'));
	return (0);
}

int	parse_error(t_source *head)
{
	t_source	*node;

	node = head;
	if (ft_strcmp(node->str, "|") == 0)
		return (syntax_error("|"));
	while (node->next)
	{
		if (node->next && node->type == OPERATOR
			&& node->next->type == OPERATOR)
		{
			if (ft_strcmp(node->str, "|"))
				return (syntax_error(node->str));
			else if (ft_strcmp(node->str, "|") == 0
				&& ft_strcmp(node->next->str, "|") == 0)
				return (syntax_error(node->str));
		}
		node = node->next;
	}
	if (node->type == OPERATOR)
		return (syntax_error(node->str));
	return (0);
}
