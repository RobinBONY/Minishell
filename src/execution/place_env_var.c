/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:48:03 by rbony             #+#    #+#             */
/*   Updated: 2022/06/03 11:21:30 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*replace_string(char *str, int start, int len, char *replace)
{
	char	*new;

	new = malloc((ft_strlen(str) - len + ft_strlen(replace))
			+ 1 * sizeof(char));
	if (!new)
		return (NULL);
	new[0] = '\0';
	ft_strncat(new, str, start);
	ft_strcat(new, replace);
	ft_strcat(new, str + (start + len));
	free(str);
	return (new);
}

char	*find_var(char *str, t_var *head)
{
	t_var	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp && ft_strncmp(str, tmp->key, ft_strlen(tmp->key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*last_exit(char *str, int start)
{
	char	*result;
	char	*exit;

	exit = ft_itoa(g_exit);
	if (!exit)
		return (NULL);
	result = replace_string(str, start, 2, exit);
	free(exit);
	return (result);
}

char	*replace_var(char *str, t_var *head)
{
	int		len;
	char	*tmp;

	tmp = str;
	if (!ft_strchr(str, '$') && *tmp != '$')
		return (str);
	while (*tmp && *tmp != '$')
	{
		if (*tmp == '\'')
			tmp = ft_strchr(tmp, '\'');
		tmp++;
	}
	len = get_type(tmp);
	if (len == -1)
		return (last_exit(str, tmp - str));
	if (len > 1)
		return (replace_string(str, tmp - str, len,
				find_var(tmp + 1, head)));
	return (str);
}

int	place_env_var(t_source *source, t_var *head)
{
	t_source	*tmp;

	tmp = source;
	while (tmp)
	{
		while (replace_needed(tmp->str, head))
		{
			tmp->str = replace_var(tmp->str, head);
			if (!tmp->str)
				return (1);
		}
		if (remove_quotes(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
