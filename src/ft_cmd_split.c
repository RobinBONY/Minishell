/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:12:29 by rbony             #+#    #+#             */
/*   Updated: 2022/03/29 13:55:38 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_splitsize(char *s)
{
	size_t	i;
	size_t	len;
	size_t	size;

	i = 0;
	len = 0;
	size = 0;
	while (s[i])
	{
		len = ft_divlen(s + i);
		if (len > 0)
		{
			size++;
			i--;
		}
		i += len;
		i++;
	}
	return (size);
}

static void	*ft_freesplit(char **split, size_t n)
{
	size_t	i;

	i = n - 1;
	while (i < n)
		free(split[i--]);
	free(split);
	return (NULL);
}

static char	**ft_splitstr(char **split, char *s, size_t size)
{
	size_t		i;
	size_t		n;

	i = 0;
	n = 0;
	while (((char *)s)[i])
	{
		size = ft_divlen((char *)s + i);
		if (size > 0)
		{
			split[n] = ft_substr(s, i--, size);
			if (!split[n])
				return (ft_freesplit(split, n));
			n++;
		}
		i = i + size + 1;
	}
	split[n] = 0;
	return (split);
}

char	**ft_cmd_split(const char *s)
{	
	size_t		size;
	char		**split;

	if (!s)
		return (NULL);
	size = ft_splitsize((char *)s);
	split = malloc((size + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (ft_splitstr(split, (char *)s, size));
}
