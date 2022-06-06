/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_src_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:12:29 by rbony             #+#    #+#             */
/*   Updated: 2022/06/06 17:53:23 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_divlen(char *s)
{
	char	*tmp;

	if (ft_strchr(s, '\'') || ft_strchr(s, '"'))
		return (ft_strlen(s));
	tmp = s;
	while (*tmp)
	{
		if (ft_isoperator(*tmp))
		{
			if (*tmp == '|')
				return (1);
			while (*tmp && *tmp != '|' && ft_isoperator(*tmp))
				tmp++;
			return (tmp - s);
		}
		if (!ft_isoperator(*tmp))
		{
			while (*tmp && !ft_isoperator(*tmp))
				tmp++;
			return (tmp - s);
		}
		tmp++;
	}
	return (tmp - s);
}

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

char	**ft_src_split(const char *s)
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
