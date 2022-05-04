/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:59:05 by rbony             #+#    #+#             */
/*   Updated: 2022/05/04 13:39:52 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
}

int	is_operator(char *str)
{
	if (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0)
		return (1);
	if (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
		return (1);
	/*if (ft_strncmp(str, "|", 1) == 0)
		return (1);*/
	return (0);
}

int	make_redirection(t_input *input, char *operator, char *filename)
{
	t_redirect	*redirect;

	// test filename
	if (!filename)
		return (1);
	if (ft_strncmp(operator, "<", 1) == 0)
		redirect = ft_rednew(1, 0, 0, ft_strdup(filename));
	else if (ft_strncmp(operator, ">", 1) == 0)
		redirect = ft_rednew(0, 1, 0, ft_strdup(filename));
	else if (ft_strncmp(operator, ">>", 2) == 0)
		redirect = ft_rednew(0, 0, 1, ft_strdup(filename));
	if (!redirect)
		return (1);
	ft_redadd_back(&(*input).redirects, redirect);
	return (0);
}

int	make_heredoc(t_input *input, char *delimiter)
{
	t_heredoc	*heredoc;

	//test delimiter
	if (!delimiter)
		return (1);
	heredoc = ft_docnew(ft_strdup(delimiter));
	if (!heredoc)
		return (1);
	ft_docadd_back(&(*input).heredocs, heredoc);
	return (0);
}

int	make_operator(t_input *input, char **words, int i)
{
	if (ft_strncmp(words[i], "<", 1) == 0
		|| ft_strncmp(words[i], ">", 1) == 0
		|| ft_strncmp(words[i], ">>", 2) == 0)
		return (make_redirection(input, words[i], words[i + 1]));
	else if (ft_strncmp(words[i], "<<", 2) == 0)
		return (make_heredoc(input, words[i + 1]));
	return (0);
}

int	get_size(char **words, int i)
{
	int	size;

	size = 0;
	while (words[i + size] && !is_operator(words[i + size]))
		size++;
	return (size);
}

int	make_cmd(t_input *input, t_var *head_env, char **words, int i)
{
	int		size;
	int		j;
	char	**arg;
	t_cmd	*cmd;

	size = get_size(words, i);
	arg = malloc ((size + 1) * sizeof(char *));
	if (!arg)
		return (0);
	j = -1;
	while (++j < size)
	{
		arg[j] = ft_strdup(words[i + j]);
		if (!arg[j])
		{
			free_tab(arg);
			return (0);
		}
	}
	arg[j] = NULL;
	cmd = ft_cmdnew(arg[0], arg);
	if (!cmd)
		return (0);
	ft_cmdadd_back(&(*input).cmds, cmd);
	return (size);
}

void	test_parsing(t_input input)
{
	int	i;

	printf("%s\n", "Input :");
	printf("%s\n", "\tHeredocs :");
	while (input.heredocs)
	{
		printf("%s%s\n", "\t\tDelimiteur : ", input.heredocs->delim);
		input.heredocs = input.heredocs->next;
	}
	printf("%s\n", "\tRedirections :");
	while (input.redirects)
	{
		printf("%s%s\n", "\t\tFilename : ", input.redirects->filename);
		printf("%s%d\n", "\t\tInput : ", input.redirects->is_input);
		printf("%s%d\n", "\t\tOutput : ", input.redirects->is_output);
		printf("%s%d\n", "\t\tAppend : ", input.redirects->is_append);
		input.redirects = input.redirects->next;
	}
	printf("%s\n", "\tCommandes :");
	while (input.cmds)
	{
		printf("%s%s\n", "\t\tCmd : ", input.cmds->path);
		i = 0;
		while (input.cmds->argv[i])
		{
			printf("\t\t%s\n", input.cmds->argv[i]);
			i++;
		}
		input.cmds = input.cmds->next;
	}
}

int	parsing(char **words, t_var *head_env)
{
	int		i;
	t_input	input;

	i = 0;
	while (words[i])
	{
		if (is_operator(words[i]))
		{
			if (make_operator(&input, words, i))
				return (1);
			i += 2;
		}
		else
		{
			i += make_cmd(&input, head_env, words, i);
		}
	}
	test_parsing(input);
	return (0);
}

int	parse_line(char *line, t_var *head_env, t_exp *head_exp)
{
	char	**words;

	if (not_interpreted(line))
		return (0);
	words = ft_cmd_split(line);
	if (!words)
		return (1);
	if (place_env_var(words, head_env) == 0)
	{
		if (parsing(words, head_env))
		{
			free_tab(words);
			return (1);
		}
	}
	free_tab(words);
	return (0);
}

/*if (ft_strcmp(words[i], "env") == 0)
				print_env(head_env);
			else if (ft_strncmp(words[i], "export", 6) == 0)
			{
				if (words[i + 1])
				{
					append_to_exp(head_exp, words[i + 1]);
					sort_export(head_exp);
				}
				else
					print_export(head_exp);
			}
			else if (ft_strcmp(words[i], "setenv") == 0)
			{
				append_to_list(head_env, words[i + 1]);
			}
			else if (ft_strcmp(words[i], "unset") == 0 && words[i + 1])
				ft_unset(head_exp, head_env, words[i + 1]);
			else if (ft_strcmp(words[i], "pwd") == 0)
				ft_pwd(head_env);
			else if (ft_strcmp(words[i], "cd") == 0)
				if (words[i + 1])
					ft_cd(words[i + 1], head_env);
				else
					ft_cd(NULL, head_env);
				//Si la variable est occurrente, l'ajouter à env ET export
				//Si la variable n'a pas de valeur, add dans export
			else
				printf("%s\n", words[i]);*/
