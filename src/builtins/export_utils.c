/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:37:00 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/13 15:12:04 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_arg(char *arg)
{
	char	*cursor;

	if (ft_strlen(arg) == 0)
		return (1);
	cursor = arg;
	if (ft_isdigit(*cursor) || *cursor == '=' || *cursor == '+')
		return (1);
	while (*cursor && (ft_isalnum(*cursor) || *cursor == '_'))
		cursor++;
	if (*cursor == '\0' || *cursor == '=' || !ft_strncmp(cursor, "+=", 2))
		return (0);
	else
		return (1);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

// char	*ft_strcat(char *dest, char *src)
// {
// 	int	i;
// 	int	next;

// 	i = 0;
// 	next = ft_strlen(dest);
// 	while (src[i])
// 	{
// 		dest[i + next] = src[i];
// 		i++;
// 	}
// 	dest[i + next] = '\0';
// 	return (dest);
// }
