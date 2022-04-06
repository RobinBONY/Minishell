/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:59:05 by rbony             #+#    #+#             */
/*   Updated: 2022/04/06 15:02:13 by alakhdar         ###   ########lyon.fr   */
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
	if (place_env_var(words) == 0)
	{	
		while (words[++i])
		{
			if (ft_strcmp(words[i], "env") == 0)
				return (2);
			if (ft_strcmp(words[i], "unset") == 0)
				ft_unset(head, words[i + 1]);
			if (ft_strcmp(words[i], "set") == 0)
				append_to_envp(head, words[i + 1]);
			else
				printf("%s\n", words[i]);
		}
	}
	free_tab(words);
	return (0);
}
