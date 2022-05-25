/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:13:43 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/25 13:25:29 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, char *src, unsigned int nb)
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
