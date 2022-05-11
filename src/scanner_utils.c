/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:17:17 by rbony             #+#    #+#             */
/*   Updated: 2022/05/09 16:12:23 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/scanner.h"
#include "../headers/source.h"

void	init_tokenizer(t_tokenizer *tokenizer, t_source *src)
{
	tokenizer->tok_buf = NULL;
	tokenizer->tok_bufsize = 0;
	tokenizer->tok_bufindex = -1;
	if (!src || !src->buffer || !src->bufsize)
		return ;
	if (!tokenizer->tok_buf)
	{
		tokenizer->tok_bufsize = 1024;
		tokenizer->tok_buf = malloc(tokenizer->tok_bufsize);
		if (!tokenizer->tok_buf)
			return ;
	}
	tokenizer->tok_bufindex = 0;
	tokenizer->tok_buf[0] = '\0';
}

void	free_token(t_token *tok)
{
	if (tok->text)
		free(tok->text);
	free(tok);
}
