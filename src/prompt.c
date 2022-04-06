/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:59:05 by rbony             #+#    #+#             */
/*   Updated: 2022/04/06 14:51:53 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
}

int	parse_line(char *line, t_var *head)
{
	int		i;
	char	**words;

	i = -1;
	if (not_interpreted(line))
		return (0);
	words = ft_cmd_split(line);
	if (!words)
		return (1);
	while (words[++i])
	{
		if (ft_strncmp(words[i], "env", ft_strlen("env")) == 0)
			print_var(head);
		if (ft_strncmp(words[i], "unset", ft_strlen("unset")) == 0)
			ft_unset(head, words[i + 1]);
		if (ft_strncmp(words[i], "set", ft_strlen("set")) == 0)
			append_to_list(head, words[i + 1]);
		else
			printf("%s\n", words[i]);
	}
	free_tab(words);
	return (0);
}

// int	main(void)
// {
// 	char	*line_buffer;

// 	while (1)
// 	{
// 		line_buffer = readline("$> ");
// 		if (line_buffer && *line_buffer)
// 		{
// 			add_history(line_buffer);
// 			if (parse_line(line_buffer))
// 				printf("%s/n", "Error");
// 		}
// 		free(line_buffer);
// 	}
// 	return (0);
// }
