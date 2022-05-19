/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:14:46 by rbony             #+#    #+#             */
/*   Updated: 2022/05/19 10:44:06 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	parse_error(t_source *head)
{
	t_source	*node;

	node = head;
	while (node->next)
	{
		if (node->next && node->type == OPERATOR
			&& node->next->type == OPERATOR)
		{
			if (ft_strcmp(node->str, "|") == 0)
				return (0);
			printf("%s\n", "minishell : syntax error");
			return (1);
		}
		node = node->next;
	}
	return (0);
}

void	assign_type(t_source *source)
{
	t_source	*src;

	src = source;
	while (src)
	{
		if (ft_isoperator(src->str[0]))
			src->type = OPERATOR;
		else
			src->type = STRING;
		src = src->next;
	}
}

int	parse_and_execute(t_env *env, char *line_buffer)
{
	t_source	*source;
	t_source	*tmp;

	source = make_source(line_buffer);
	if (!source)
		return (1);
	assign_type(source);
	if (parse_error(source))
		return (1);
	tmp = source;
	while (tmp)
	{
		printf("%d %s\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env		env;
	char		*line_buffer;

	env.head_var = init_env(envp);
	env.head_exp = init_export(envp);
	if (!env.head_exp)
		return (1);
	env.head_exp = sort_export(env.head_exp);
	while (1)
	{
		line_buffer = readline("Minishell2.0$> ");
		if (line_buffer && *line_buffer)
		{
			add_history(line_buffer);
			parse_and_execute(&env, line_buffer);
		}
	}
	return (0);
}
