/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:47:56 by rbony             #+#    #+#             */
/*   Updated: 2022/05/09 16:11:49 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/parser.h"
#include "../headers/scanner.h"
#include "../headers/node.h"
#include "../headers/source.h"

t_node	*make_nodes(t_node *cmd, t_token *tok)
{
	t_source	*src;
	t_node		*word;

	src = tok->src;
	while (tok != 0)
	{
		if (tok->text[0] == '\n')
		{
			free_token(tok);
			break ;
		}
		word = new_node(NODE_VAR);
		if (!word)
		{
			free_node_tree(cmd);
			free_token(tok);
			return (NULL);
		}
		set_node_val_str(word, tok->text);
		add_child_node(cmd, word);
		free_token(tok);
		tok = tokenize(src);
	}
	return (cmd);
}

t_node	*parse_simple_command(t_token *tok)
{
	t_node		*cmd;

	if (!tok)
	{
		return (NULL);
	}
	cmd = new_node(NODE_COMMAND);
	if (!cmd)
	{
		free_token(tok);
		return (NULL);
	}
	return (make_nodes(cmd, tok));
}
