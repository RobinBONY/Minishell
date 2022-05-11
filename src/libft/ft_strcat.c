/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:53:03 by rbony             #+#    #+#             */
/*   Updated: 2022/05/10 08:54:08 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	dest[i + next] = '\0';
	return (dest);
}
