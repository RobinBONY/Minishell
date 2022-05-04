/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:18:38 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/04 13:19:01 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	lenght;

	lenght = 0;
	while (str[lenght] != '\0')
	{
		lenght++;
	}
	return (lenght);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	lenght;
	unsigned int	lenghtsrc;

	lenght = 0;
	lenghtsrc = ft_strlen(src);
	while (lenght != n)
	{
		if (lenght <= lenghtsrc)
		{
			dest[lenght] = src[lenght];
		}
		else
		{
			dest[lenght] = '\0';
		}
		lenght++;
	}
	return (dest);
}
