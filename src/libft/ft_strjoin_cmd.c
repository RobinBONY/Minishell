/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:53:45 by rbony             #+#    #+#             */
/*   Updated: 2022/05/10 08:54:38 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_cmd(const char *s1, const char *s2)
{
	char	*concat;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	concat = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 2);
	if (!concat)
		return (NULL);
	concat[0] = '\0';
	ft_strcat(concat, (char *)s1);
	ft_strcat(concat, "/");
	ft_strcat(concat, (char *)s2);
	return (concat);
}
