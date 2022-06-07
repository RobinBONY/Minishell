/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:17:33 by rbony             #+#    #+#             */
/*   Updated: 2022/06/07 13:18:16 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	is_numeric(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(char *ex_no)
{
	unlink("/tmp/.heredoc");
	if (!ex_no)
		exit(0);
	if (is_numeric(ex_no))
		exit(ft_atol(ex_no));
	else
	{
		printf("%s\n", "exit");
		printf("Minishell: exit: %s: numeric argument required\n",
			ex_no);
		exit(255);
	}
}
