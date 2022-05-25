/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:14:46 by rbony             #+#    #+#             */
/*   Updated: 2022/05/25 12:20:11 by rbony            ###   ########lyon.fr   */
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
			if (ft_strcmp(node->str, "|"))
			{
				printf("%s\n", "minishell : syntax error");
				return (1);
			}
		}
		node = node->next;
	}
	if (node->type == OPERATOR)
	{
		printf("%s\n", "minishell : syntax error");
		return (1);
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

int	find_heredocs(t_executor *exec, t_source **source)
{
	t_source	*tmp;
	t_heredoc	*new;

	tmp = *source;
	exec->heredocs = NULL;
	while (tmp)
	{
		if (tmp->type == OPERATOR && tmp->used
			&& ft_strcmp(tmp->str, "<<") == 0)
		{
			new = new_heredoc(tmp->next->str);
			if (!new)
				return (1);
			ft_docadd_front(&exec->heredocs, new);
			tmp->used = 0;
			tmp->next->used = 0;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	open_infile(char *infile)
{
	int	fd_file;

	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
	{
		perror("Error");
		return (-1);
	}
	else
	{
		fd_file = open(infile, O_RDONLY);
		if (fd_file == -1)
			return (-1);
	}
	return (fd_file);
}

int	open_outfile(char *outfile)
{
	int	fd_file;

	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		perror("Error");
		return (-1);
	}
	else
	{
		fd_file = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd_file == -1)
			return (-1);
	}
	return (fd_file);
}

int	open_append(char *outfile)
{
	int	fd_file;

	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		perror("Error");
		return (-1);
	}
	else
	{
		fd_file = open(outfile, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd_file == -1)
			return (-1);
	}
	return (fd_file);
}

void	set_input(t_executor *exec, t_source *tmp)
{
	exec->input = open_infile(tmp->next->str);
	tmp->used = 0;
	tmp->next->used = 0;
}

void	set_output(t_executor *exec, t_source *tmp, int mode)
{
	if (mode)
		exec->output = open_append(tmp->next->str);
	else
		exec->output = open_outfile(tmp->next->str);
	tmp->used = 0;
	tmp->next->used = 0;
}

int	find_redirects(t_executor *exec, t_source **source)
{
	t_source	*tmp;

	tmp = *source;
	while (tmp)
	{
		if (tmp->type == OPERATOR && tmp->used
			&& ft_strcmp(tmp->str, "<") == 0)
			set_input(exec, tmp);
		else if (tmp->type == OPERATOR && tmp->used
			&& ft_strcmp(tmp->str, ">") == 0)
			set_output(exec, tmp, 0);
		else if (tmp->type == OPERATOR && tmp->used
			&& ft_strcmp(tmp->str, ">>") == 0)
			set_output(exec, tmp, 1);
		tmp = tmp->next;
	}
	if (exec->input == -1 || exec->output == -1)
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

t_cmd	*new_cmd(t_source **source, t_cmd *prev, int len)
{
	t_cmd		*new;
	int			i;

	i = 0;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argv = malloc((len + 1) * sizeof(char *));
	if (!new->argv)
		return (NULL);
	while (*source && i < len)
	{
		if ((*source)->used)
		{
			new->argv[i] = ft_strdup((*source)->str);
			(*source)->used = 0;
			i++;
		}
		*source = (*source)->next;
	}
	new->argv[i] = NULL;
	new->is_builtin = is_builtin(new->argv[0]);
	new->next = NULL;
	new->prev = prev;
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
		if (tmp->used)
			i++;
		tmp = tmp->next;
	}
	if (tmp)
		tmp->used = 0;
	return (i);
}

void	index_commands(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmds;
	i = 1;
	while (tmp)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
}

int	make_commands(t_executor *exec, t_source **source)
{
	int			cmd_len;
	t_cmd		*new;
	t_source	*tmp;

	exec->commands = NULL;
	tmp = *source;
	while (tmp)
	{
		cmd_len = get_len(tmp);
		if (cmd_len > 0)
		{
			new = new_cmd(&tmp, new, cmd_len);
			if (!new)
				return (1);
			ft_cmdadd_back(&exec->commands, new);
		}
		else
			tmp = tmp->next;
	}
	index_commands(exec->commands);
	return (0);
}

void	*free_executor(t_executor **exec)
{
	t_heredoc	*doctmp;
	t_cmd		*cmdtmp;

	doctmp = (*exec)->heredocs;
	cmdtmp = (*exec)->commands;
	while ((*exec)->heredocs)
	{
		doctmp = (*exec)->heredocs->next;
		free((*exec)->heredocs->str);
		free((*exec)->heredocs);
		(*exec)->heredocs = doctmp;
	}
	while ((*exec)->commands)
	{
		cmdtmp = (*exec)->commands->next;
		free((*exec)->commands->path);
		free_tab((*exec)->commands->argv);
		free((*exec)->commands);
		(*exec)->commands = cmdtmp;
	}
	free(*exec);
	return (NULL);
}

t_executor	*make_executor(t_source	*source, t_env *env)
{
	t_executor	*executor;

	executor = malloc(sizeof(t_executor));
	if (!executor)
		return (NULL);
	executor->input = 0;
	executor->output = 0;
	if (find_heredocs(executor, &source))
		return (free_executor(&executor));
	if (place_env_var(source, env->head_var))
		return (free_executor(&executor));
	if (find_redirects(executor, &source))
		return (free_executor(&executor));
	if (make_commands(executor, &source))
		return (free_executor(&executor));
	return (executor);
}

void	ft_srcclear(t_source **head)
{
	t_source	*cursor;

	while (*head)
	{
		cursor = (*head)->next;
		if ((*head)->str)
			free((*head)->str);
		free((*head));
		*head = cursor;
	}
}

int	unmanaged_character_error(char c)
{
	printf("%s%c\n", "Unmanaged character : ", c);
	return (1);
}

int	check_quotes(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (*tmp == '\'')
		{
			tmp = ft_strchr(tmp, '\'');
			if (!tmp)
				return (unmanaged_character_error('\''));
		}
		else if (*tmp == '"')
		{
			tmp = ft_strchr(tmp, '"');
			if (!tmp)
				return (unmanaged_character_error('"'));
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

int	parse_and_execute(t_env *env, char *line_buffer)
{
	t_source	*source;
	t_executor	*exec;

	if (not_interpreted(line_buffer))
		return (1);
	source = make_source(line_buffer);
	if (!source)
		return (1);
	assign_type(source);
	if (parse_error(source))
	{
		ft_srcclear(&source);
		return (1);
	}
	exec = make_executor(source, env);
	if (!exec)
		return (1);
	ft_srcclear(&source);
	execution(env, exec);
	free_executor(&exec);
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
			free(line_buffer);
		}
	}
	return (0);
}
