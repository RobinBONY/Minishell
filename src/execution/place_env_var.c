/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:48:03 by rbony             #+#    #+#             */
/*   Updated: 2022/06/02 14:38:53 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*replace_string(char *str, int start, int len, char *replace)
{
	char	*new;
	int		boo;

	boo = 0;
	if (!replace)
	{
		replace = malloc(1);
		if (!replace)
			return (NULL);
		replace[0] = '\0';
		boo = 1;
	}
	new = malloc((ft_strlen(str) - len + ft_strlen(replace))
			+ 1 * sizeof(char));
	if (!new)
		return (NULL);
	new[0] = '\0';
	ft_strncat(new, str, start);
	ft_strcat(new, replace);
	ft_strcat(new, str + (start + len));
	free(str);
	if (boo)
		free(replace);
	return (new);
}

char	*find_var(char *str, int len, t_var *head)
{
	t_var	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp && ft_strncmp(str, tmp->key, len) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*last_exit(char *str, int start, int len)
{
	char	*result;
	char	*exit;

	exit = ft_itoa(g_exit);
	if (!exit)
		return (NULL);
	result = replace_string(str, start, len, exit);
	free(exit);
	return (result);
}

char	*replace_var(char *str, t_var *head)
{
	int		len;
	char	*tmp;
	char	*replace;
	char	*exit;

	tmp = str;
	len = 0;
	if (!str || (!ft_strchr(str, '$') && *str != '$'))
		return (str);
	while (*tmp && *tmp != '$')
	{
		if (*tmp == '\'')
			tmp = ft_strchr(tmp, '\'');
		tmp++;
	}
	if (*(tmp + 1) && *(tmp + 1) == '?')
		return (last_exit(str, tmp - str, 2));
	len++;
	while (tmp[len] && tmp[len] != '\'' && tmp[len] != ' ' && tmp[len] != '"'
		&& tmp[len] != '$')
		len++;
	if (len > 1)
		return (replace_string(str, tmp - str, len,
				find_var(tmp + 1, len - 1, head)));
	return (str);
}

int	place_env_var(t_source *source, t_var *head)
{
	t_source	*tmp;

	tmp = source;
	while (tmp)
	{
		if (replace_needed(tmp->str, head))
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
