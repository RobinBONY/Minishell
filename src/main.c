/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:14:46 by rbony             #+#    #+#             */
/*   Updated: 2022/05/19 14:57:46 by rbony            ###   ########lyon.fr   */
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

t_heredoc	*new_heredoc(char *delim)
{
	t_heredoc	*new;

	new = malloc(sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->str = ft_strdup(delim);
	new->next = NULL;
	return (new);
}

void	ft_docadd_front(t_heredoc **alst, t_heredoc *new)
{
	t_heredoc	*next;

	next = *alst;
	*alst = new;
	new->next = next;
}

void	ft_cmdadd_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*last;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = *alst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	pop(t_source **source, t_source *used)
{
	t_source	*tmp;

	tmp = *source;
	if (&(*tmp) == &(*used))
	{
		source = &used->next->next;
		tmp = used->next;
	}
	else
	{
		while (&(*tmp).next != &(*used))
		{
			tmp = tmp->next;
		}
		tmp->next = used->next->next;
		tmp = used->next;
	}
	free(used->str);
	free(tmp->str);
	free(used);
	free(tmp);
}

int	find_heredocs(t_executor *exec, t_source **source)
{
	t_source	*tmp;
	t_heredoc	*new;

	tmp = *source;
	exec->heredocs = NULL;
	while (tmp)
	{
		if (tmp->type == OPERATOR && ft_strcmp(tmp->str, "<<") == 0)
		{
			if (tmp->next && tmp->next->type == STRING)
			{
				new = new_heredoc(tmp->str);
				if (!new)
					return (1);
				ft_docadd_front(exec->heredocs, new);
				pop(source, tmp);
			}
			else
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	find_redirects(t_executor *exec, t_source **source)
{
	t_source	*tmp;

	tmp = *source;
	exec->append_mode = 0;
	while (tmp)
	{
		if (tmp->type == OPERATOR && ft_strcmp(tmp->str, "<") == 0)
		{
			exec->input = ft_strdup(tmp->next->str);
			pop(source, tmp);
		}
		else if (tmp->type == OPERATOR && ft_strcmp(tmp->str, ">") == 0)
		{
			exec->output = ft_strdup(tmp->next->str);
			pop(source, tmp);
		}
		else if (tmp->type == OPERATOR && ft_strcmp(tmp->str, ">>") == 0)
		{
			exec->output = ft_strdup(tmp->next->str);
			exec->append_mode = 1;
			pop(source, tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_cmd	*new_cmd(t_source *source, int len)
{
	t_cmd		*new;
	int			i;

	i = -1;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argv = malloc((len + 1) * sizeof(char *));
	if (!new->argv)
		return (NULL);
	while (++i < len)
	{
		new->argv[i] = ft_strdup(source->str);
		source = source->next;
	}
	new->argv[i] = NULL;
	new->path = ft_strdup(new->argv[0]);
	new->next = NULL;
	return (new);
}

int	get_len(t_source *src)
{
	int			i;
	t_source	*tmp;

	i = 0;
	tmp = src;
	while (tmp && ft_strcmp(tmp->str, "|"))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	make_commands(t_executor *exec, t_source **source)
{
	int			cmd_len;
	int			i;
	t_cmd		*new;
	t_source	*tmp;

	exec->commands = NULL;
	while (*source)
	{
		cmd_len = get_len(*source);
		new = new_cmd(*source, cmd_len);
		if (!new)
			return (1);
		ft_cmdadd_back(&exec->commands, new);
		i = -1;
		while (++i <= cmd_len)
		{
			tmp = *source;
			*source = (*source)->next;
			free(tmp->str);
			free(tmp);
		}
	}
	return (0);
}

t_executor	*make_executor(t_source	*source)
{
	t_executor	*executor;

	executor = malloc(sizeof(t_executor));
	if (!executor)
		return (NULL);
	if (find_heredocs(executor, &source))
		return (NULL);
	if (find_redirects(executor, &source))
		return (NULL);
	if (make_commands(executor, &source))
		return (NULL);
	return (executor);
}

int	parse_and_execute(t_env *env, char *line_buffer)
{
	t_source	*source;
	t_executor	*exec;

	source = make_source(line_buffer);
	if (!source)
		return (1);
	assign_type(source);
	if (parse_error(source))
		return (1);
	exec = make_executor(source);
	if (!exec)
		return (1);
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
