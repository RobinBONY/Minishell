/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:20:58 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/03 16:25:17 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	unmanaged_character_error(char c)
{
	printf("Minishell : unmanaged character :\'%c\'\n", c);
	g_exit = -1;
	return (1);
}

int	cmd_not_found(char *str)
{
	printf("Minishell : command not found : %s\n", str);
	g_exit = 127;
	return (1);
}

int	unclosed_quote(char c)
{
	printf("Minishell : unexpected EOF while looking for matching\'%c\'\n", c);
	g_exit = -1;
	return (1);
}

int	syntax_error(char c)
{
	printf("Minishell : syntax error near unexpected token \'%c\'\n", c);
	g_exit = 258;
	return (1);
}
