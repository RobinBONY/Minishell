/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:48:03 by rbony             #+#    #+#             */
/*   Updated: 2022/04/12 15:39:52 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	next;

	i = 0;
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

	new = malloc((ft_strlen(str) - len + ft_strlen(replace)) * sizeof(char));
	if (!new)
		return (NULL);
	new[0] = '\0';
	ft_strncat(new, str, start);
	ft_strcat(new, replace);
	ft_strcat(new, str + (start + len));
	free(str);
	return (new);
}

static char	*replace_var(char *str)
{
	int		len;
	char	*tmp;
	char	*replace;

	tmp = str;
	len = 0;
	while (*tmp && *tmp != '$')
		tmp++;
	while (tmp[len] && tmp[len] != ' ')
		len++;
	if (len > 1)
		return (replace_string(str, tmp - str, len, "prout"));
	return (str);
}

int	place_env_var(char **words)
{
	int	i;

	i = -1;
	while (words[++i])
	{
		if (replace_needed(words[i]))
		{
			words[i] = replace_var(words[i]);
			if (!words[i])
				return (1);
		}
	}
	return (0);
}
