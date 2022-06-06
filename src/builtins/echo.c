/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:28:49 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/06 15:19:02 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_new_line(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **arg)
{
	int	i;
	int	newline;

	i = 1;
	newline = 0;
	while (arg[i] && check_new_line(arg[i]))
	{
		newline = 1;
		i++;
	}
	while (arg[i])
	{
		printf("%s ", arg[i]);
		i++;
	}
	if (!newline)
		printf("\n");
	return (0);
}
