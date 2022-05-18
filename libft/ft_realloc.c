/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:13:04 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/10 10:30:27 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	current_size;

	if (ptr == 0)
		return (malloc(newsize));
	current_size = sizeof(ptr);
	if (newsize <= current_size)
		return (ptr);
	newptr = malloc(newsize);
	ft_memcpy(ptr, newptr, current_size);
	free(ptr);
	return (newptr);
}
