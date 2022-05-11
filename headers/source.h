/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:13:16 by rbony             #+#    #+#             */
/*   Updated: 2022/05/05 14:28:12 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOURCE_H
# define SOURCE_H

typedef struct s_source
{
	char	*buffer;
	long	bufsize;
	long	curpos;
}	t_source;

char	next_char(t_source *src);
void	unget_char(t_source *src);
char	peek_char(t_source *src);
void	skip_white_spaces(t_source *src);

#endif 