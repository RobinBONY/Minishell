/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:14:46 by rbony             #+#    #+#             */
/*   Updated: 2022/05/10 13:35:59 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	parse_and_execute(t_source *src, t_var	*head_env, t_exp *head_exp)
{
	t_token	*tok;
	t_node	*cmd;

	skip_white_spaces(src);
	tok = tokenize(src);
	if (tok == 0)
	{
		return (0);
	}
	while (tok && tok != 0)
	{
		cmd = parse_simple_command(tok);
		if (!cmd)
		{
			break ;
		}
		do_simple_command(cmd, head_env, head_exp);
		free_node_tree(cmd);
		tok = tokenize(src);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_source	src;
	t_var		*head_env;
	t_exp		*head_exp;
	char		*line_buffer;

	head_env = init_env(envp);
	head_exp = init_export(envp);
	head_exp = sort_export(head_exp);
	while (1)
	{
		line_buffer = readline("minishell2.0$> ");
		if (line_buffer && *line_buffer)
		{
			add_history(line_buffer);
			src.buffer = line_buffer;
			src.bufsize = ft_strlen(line_buffer);
			src.curpos = -2;
			parse_and_execute(&src, head_env, head_exp);
		}
	}
	return (0);
}
