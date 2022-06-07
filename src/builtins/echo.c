/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:28:49 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/07 13:39:02 by rbony            ###   ########lyon.fr   */
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

int	something_after(char **arg, int i)
{
	int	result;

	result = 0;
	while (arg[++i])
	{
		if (*arg[i] != '\0')
			result = 1;
	}
	return (result);
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
		printf("%s", arg[i]);
		if (something_after(arg, i))
			printf("%s", " ");
		i++;
	}
	if (!newline)
		printf("\n");
	return (0);
}
