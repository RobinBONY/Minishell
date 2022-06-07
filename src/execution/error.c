/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:20:58 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/07 13:13:54 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	unmanaged_character_error(char c)
{
	printf("\033[91mUnmanaged character \'%c\'\033[0m\n", c);
	g_exit = -1;
	return (1);
}

int	cmd_not_found(char *str)
{
	printf("\033[91m%s: command not found\033[0m\n", str);
	g_exit = 127;
	return (1);
}

int	unclosed_quote(char c)
{
	printf("\033[91mUnexpected EOF while looking for matching `%c\'\n\033[0m",
		c);
	g_exit = -1;
	return (1);
}

int	syntax_error(char *c)
{
	printf("\033[91mSyntax error near unexpected token \'%s\'\033[0m\n", c);
	g_exit = 258;
	return (1);
}
