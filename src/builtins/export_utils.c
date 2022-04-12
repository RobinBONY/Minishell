/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:37:00 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/12 14:19:42 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_arg(char *arg)
{
	char	*cursor;

	if (ft_strlen(arg) == 0)
		return (export_error(arg));
	cursor = arg;
	if (ft_isdigit(*cursor) || *cursor == '=' || *cursor == '+')
		return (export_error(arg));
	while (*cursor && (ft_isalnum(*cursor) || *cursor == '_'))
		cursor++;
	if (*cursor == '\0' || *cursor == '=' || !ft_strncmp(cursor, "+=", 2))
		return (0);
	else
		return (1);
}
