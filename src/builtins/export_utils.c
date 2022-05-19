/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:37:00 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/16 16:33:41 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
