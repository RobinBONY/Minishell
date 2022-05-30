/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:59:33 by rbony             #+#    #+#             */
/*   Updated: 2022/05/30 12:59:47 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*concat;

	if (!s1 || !s2)
		return (NULL);
	concat = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!concat)
		return (NULL);
	ft_strcpy(concat, (char *)s1);
	ft_strcat(concat, (char *)s2);
	return (concat);
}
