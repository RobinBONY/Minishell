/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:20:58 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/06 19:02:18 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	unmanaged_character_error(char c)
{
	printf("bash: unmanaged character \'%c\'\n", c);
	g_exit = -1;
	return (1);
}

int	cmd_not_found(char *str)
{
	printf("bash: %s: command not found\n", str);
	g_exit = 127;
	return (1);
}

int	unclosed_quote(char c)
{
	printf("bash: unexpected EOF while looking for matching \'%c\'\n", c);
	g_exit = -1;
	return (1);
}

int	syntax_error(char *c)
{
	printf("bash: syntax error near unexpected token \'%s\'\n", c);
	g_exit = 258;
	return (1);
}
