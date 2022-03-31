/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:59:05 by rbony             #+#    #+#             */
/*   Updated: 2022/03/31 14:50:52 by rbony            ###   ########lyon.fr   */
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

int	parse_line(char *line)
{
	int		i;
	char	**words;

	i = -1;
	if (not_interpreted(line))
		return (0);
	words = ft_cmd_split(line);
	if (!words)
		return (1);
	if (place_env_var(words) == 0)
	{
		while (words[++i])
			printf("%s\n", words[i]);
	}
	free_tab(words);
	return (0);
}

int	main(void)
{
	char	*line_buffer;

	while (1)
	{
		line_buffer = readline("$> ");
		if (line_buffer && *line_buffer)
		{
			add_history(line_buffer);
			if (parse_line(line_buffer))
				printf("%s/n", "Error");
		}
		free(line_buffer);
	}
	return (0);
}
