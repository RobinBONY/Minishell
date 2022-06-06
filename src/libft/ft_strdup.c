/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:06:47 by rbony             #+#    #+#             */
/*   Updated: 2022/06/06 13:52:43 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*str;

	if (!src)
		return (NULL);
	str = malloc(ft_strlen(src) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	return (ft_strcpy(str, (char *)src));
}
