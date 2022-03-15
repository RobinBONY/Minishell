/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:59:05 by rbony             #+#    #+#             */
/*   Updated: 2022/03/15 17:32:33 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

int	main(void)
{
	char	*line_buffer;

	while (1)
	{
		line_buffer = readline("$> ");
		if (line_buffer && *line_buffer)
		{
			add_history(line_buffer);
			ft_putendl_fd(line_buffer, 1);
			free(line_buffer);
		}
	}
	return (0);
}
