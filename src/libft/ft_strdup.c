/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:06:47 by rbony             #+#    #+#             */
/*   Updated: 2022/05/10 14:50:12 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*str;

	str = malloc(ft_strlen(src) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	return (ft_strcpy(str, (char *)src));
}
