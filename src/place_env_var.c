/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:48:03 by rbony             #+#    #+#             */
/*   Updated: 2022/05/25 12:35:19 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	replace_needed(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (*tmp == '\'')
			tmp = ft_strchr(tmp, '\'');
		if (*tmp == '$')
			return (1);
		tmp++;
	}
	return (0);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	next;

	i = 0;
	if (!src)
		return (dest);
	next = ft_strlen(dest);
	while (src[i])
	{
		dest[i + next] = src[i];
		i++;
	}
	dest[i + next] = src[i];
	return (dest);
}

static char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	src_len;
	unsigned int	next;

	next = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	while (src[i] && i < nb)
	{
		dest[i + next] = src[i];
		i++;
	}
	dest[i + next] = '\0';
	return (dest);
}

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

char	*last_exit(char *str, int start, int len)
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

static char	*replace_var(char *str, t_var *head)
{
	int		len;
	char	*tmp;
	char	*replace;
	char	*exit;

	tmp = str;
	len = 0;
	while (*tmp && *tmp != '$')
		tmp++;
	if (*(tmp + 1) == '?')
		return (last_exit(str, str - tmp, 2));
	len++;
	while (tmp[len] && (ft_isalnum(tmp[len])))
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
		if (replace_needed(tmp->str))
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
