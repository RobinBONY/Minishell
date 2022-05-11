/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:15:20 by rbony             #+#    #+#             */
/*   Updated: 2022/05/05 14:27:49 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/source.h"

void	unget_char(t_source *src)
{
	if (src->curpos < 0)
	{
		return ;
	}
	src->curpos--;
}

char	next_char(t_source *src)
{
	char	c1;

	if (!src || !src->buffer)
	{
		return (0);
	}
	c1 = 0;
	if (src->curpos == -2)
	{
		src->curpos = -1;
	}
	else
	{
		c1 = src->buffer[src->curpos];
	}
	if (++src->curpos >= src->bufsize)
	{
		src->curpos = src->bufsize;
		return (-1);
	}
	return (src->buffer[src->curpos]);
}

char	peek_char(t_source *src)
{
	long	pos;

	if (!src || !src->buffer)
	{
		return (0);
	}
	pos = src->curpos;
	if (pos == -2)
	{
		pos++;
	}
	pos++;
	if (pos >= src->bufsize)
	{
		return (-1);
	}
	return (src->buffer[pos]);
}

void	skip_white_spaces(t_source *src)
{
	char	c;

	if (!src || !src->buffer)
	{
		return ;
	}
	c = peek_char(src);
	while ((c != EOF) && (c == ' ' || c == '\t'))
	{
		next_char(src);
		c = peek_char(src);
	}
}
