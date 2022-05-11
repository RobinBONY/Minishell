/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:46:16 by rbony             #+#    #+#             */
/*   Updated: 2022/05/10 11:18:28 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/scanner.h"
#include "../headers/source.h"

void	add_to_buf(char c, t_tokenizer *tokenizer)
{
	char	*tmp;

	tokenizer->tok_buf[tokenizer->tok_bufindex++] = c;
	if (tokenizer->tok_bufindex >= tokenizer->tok_bufsize)
	{
		tmp = ft_realloc(tokenizer->tok_buf, tokenizer->tok_bufsize * 2);
		if (!tmp)
			return ;
		tokenizer->tok_buf = tmp;
		tokenizer->tok_bufsize *= 2;
	}
}

t_token	*create_token(char *str)
{
	char	*nstr;
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	ft_memset(tok, 0, sizeof(t_token));
	tok->text_len = ft_strlen(str);
	nstr = malloc(tok->text_len + 1);
	if (!nstr)
	{
		free(tok);
		return (NULL);
	}
	ft_strcpy(nstr, str);
	tok->text = nstr;
	return (tok);
}

void	browse_src(char nc, t_source *src, t_tokenizer *tokenizer)
{
	int			endloop;

	endloop = 0;
	while (nc != -1)
	{
		if (nc == ' ' || nc == '\t')
		{
			if (tokenizer->tok_bufindex > 0)
					endloop = 1;
		}
		else if (nc == '\n')
		{
			if (tokenizer->tok_bufindex > 0)
				unget_char(src);
			else
				add_to_buf(nc, tokenizer);
			endloop = 1;
		}
		else
			add_to_buf(nc, tokenizer);
		if (endloop)
			break ;
		nc = next_char(src);
	}
}

t_token	*tokenize(t_source *src)
{
	char		nc;
	t_token		*tok;
	t_tokenizer	tokenizer;

	init_tokenizer(&tokenizer, src);
	nc = next_char(src);
	if (nc == 0 || nc == -1)
		return (0);
	browse_src(nc, src, &tokenizer);
	if (tokenizer.tok_bufindex == 0)
		return (0);
	if (tokenizer.tok_bufindex >= tokenizer.tok_bufsize)
		tokenizer.tok_bufindex--;
	tokenizer.tok_buf[tokenizer.tok_bufindex] = '\0';
	tok = create_token(tokenizer.tok_buf);
	if (!tok)
		return (0);
	tok->src = src;
	return (tok);
}
