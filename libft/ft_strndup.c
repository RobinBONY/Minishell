/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:35:44 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/04 13:39:27 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, unsigned int n)
{
	char	*str;

	str = malloc(n * sizeof(char) + 1);
	if (!str)
		return (NULL);
	return (ft_strncpy(str, (char *)src, n));
}
