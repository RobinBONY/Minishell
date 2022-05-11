/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:43:59 by rbony             #+#    #+#             */
/*   Updated: 2022/05/09 16:03:13 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "source.h"

typedef struct s_token
{
	struct s_source	*src;
	int				text_len;
	char			*text;
}	t_token;

typedef struct s_tokenizer
{
	char	*tok_buf;
	int		tok_bufsize;
	int		tok_bufindex;
}	t_tokenizer;

t_token	*tokenize(t_source *src);
void	free_token(t_token *tok);
void	init_tokenizer(t_tokenizer *tokenizer, t_source *src);

#endif 